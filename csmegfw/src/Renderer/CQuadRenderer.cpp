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

CQuadRenderer::CQuadRenderer() : m_currentTexture(nullptr), m_currentMethod(RenderMethod::NOT_SET)
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

void CQuadRenderer::render(Texture2D* texture, const TRectangle& rect, float rot, const Color& color)
{
    setMethodAndTexture(RenderMethod::TEXTURED, texture);
    render(rect, rot, color);
}

void CQuadRenderer::render(const TRectangle& rect, float rot, const Color& color)
{
    if(m_currentMethod == RenderMethod::NOT_SET) {
        throw CSmegException("QuandRenderer trying to render with current method == NOT_SET");
    }

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(rect.position(), 0.0f));
    model = glm::translate(model, glm::vec3(0.5f*rect.size().x, 0.5f*rect.size().y, 0.0f));
    model = glm::rotate(model, rot, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f*rect.size().x, -0.5f*rect.size().y, 0.0f));
    model = glm::scale(model, glm::vec3(rect.size(), 1.0f));

    m_currentMethodShader->set("quadColor", color.asVec4());
    m_currentMethodShader->set("model", model);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


void CQuadRenderer::initRenderMethod(RenderMethod method, ShaderProgramPtr shaderPtr)
{
    if(method != RenderMethod::NOT_SET) {
        m_methods[method] = shaderPtr;
    }
}

void CQuadRenderer::setCurrentRenderMethod(RenderMethod method)
{
    if(m_methods.count(method) == 1) {
        m_currentMethod = method;
        m_currentMethodShader = m_methods[method];
        m_currentMethodShader->use();
    }
    else {
        throw new CSmegException(
            "Trying to access uninitialized render method in CQuadRenderer, method=", 
            static_cast<int>(method));
    }
}

void CQuadRenderer::setProjection(const glm::mat4& projection)
{
    for(auto& method : m_methods) {
        method.second->use();
        method.second->set("projection", projection);
    }
}

void CQuadRenderer::setMethodAndTexture(RenderMethod method, Texture2D* texture)
{
    if(method != m_currentMethod) {
        setCurrentRenderMethod(method);
    }

    if(texture!=nullptr && texture != m_currentTexture && method == RenderMethod::TEXTURED) {
        glActiveTexture(GL_TEXTURE0);
        m_currentMethodShader->set("image", 0);
        m_currentTexture = texture;
        texture->bind();
    }

}
