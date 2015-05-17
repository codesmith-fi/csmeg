#include "CQuadRenderer.h"
#include "CShaderProgram.h"
#include "Texture2D.h"
#include "TRectangle.h"
#include "Color.h"
#include "CSmegException.h"
#include <glm/gtc/matrix_transform.hpp>

using csmeg::TRectangle;
using csmeg::Color;
using namespace csmeg::renderer;

CQuadRenderer::CQuadRenderer()
{
    init();
}

CQuadRenderer::~CQuadRenderer()
{
    glDeleteBuffers(2, m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void CQuadRenderer::init()
{
    GLfloat vert[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    GLfloat tex[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    GLuint vbo[2];

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(QR_VBO_COUNT, vbo); // vert, tex

    glBindBuffer(GL_ARRAY_BUFFER, vbo[QR_VBO_VERTEXPOS]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
    glEnableVertexAttribArray(QR_VBO_VERTEXPOS);
    glVertexAttribPointer(QR_VBO_VERTEXPOS, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[QR_VBO_TEXCOORD]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*2*6, tex, GL_STATIC_DRAW);
    glEnableVertexAttribArray(QR_VBO_TEXCOORD);
    glVertexAttribPointer(QR_VBO_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
}

void CQuadRenderer::render(Texture2D& texture, const TRectangle& rect, float rot, const Color& color)
{
    render(&texture, rect, rot, color, RenderMethod::TEXTURED);
}

void CQuadRenderer::render(const TRectangle& rect, float rot, const Color& color)
{
    render(nullptr, rect, rot, color, RenderMethod::FLATCOLOR);
}

void CQuadRenderer::render(Texture2D* texture, const TRectangle& rect, float rot, const Color& color, RenderMethod method)
{
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(rect.position(), 0.0f));
    model = glm::translate(model, glm::vec3(0.5f*rect.size().x, 0.5f*rect.size().y, 0.0f));
    model = glm::rotate(model, rot, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f*rect.size().x, -0.5f*rect.size().y, 0.0f));
    model = glm::scale(model, glm::vec3(rect.size(), 1.0f));
    glm::mat4 mvp = m_projectionMatrix * m_viewMatrix * model;

    m_shaderProgram->use();

    if(method == RenderMethod::TEXTURED) {
        setTexture(texture);
        m_shaderProgram->set("enableTexture", 1);
    }
    else {
        m_shaderProgram->set("enableTexture", 0);
    }

    m_shaderProgram->set("quadColor", color.asVec4());
    m_shaderProgram->set("mvp", mvp);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void CQuadRenderer::setProjection(const glm::mat4& projection)
{
    m_projectionMatrix = projection;
}

void CQuadRenderer::setView(const glm::mat4& view)
{
    m_viewMatrix = view;
}

void CQuadRenderer::setShaderProgram(ShaderProgramPtr shader)
{
    m_shaderProgram = shader;
}

void CQuadRenderer::setTexture(Texture2D* texture)
{
    if((texture != nullptr), (texture->id() != m_boundTextureId)) {
        glActiveTexture(GL_TEXTURE0);
        m_shaderProgram->set("image", 0);
        m_boundTextureId = texture->bind();
    }
}

