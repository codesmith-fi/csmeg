#include "CQuadRenderer.h"
#include "CShaderProgram.h"
#include "Texture2D.h"
#include "TRectangle.h"

#include <glm/gtc/matrix_transform.hpp>

using csmeg::TRectangle;
using namespace csmeg::renderer;

CQuadRenderer::CQuadRenderer(CShaderProgram& shader) : m_shader(shader)
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

void CQuadRenderer::render(Texture2D& texture, const TRectangle& rect, float rot, const glm::vec3& color)
{
    m_shader.use();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(rect.position(), 0.0f));
    model = glm::translate(model, glm::vec3(0.5f*rect.size().x, 0.5f*rect.size().y, 0.0f));
    model = glm::rotate(model, rot, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f*rect.size().x, -0.5f*rect.size().y, 0.0f));
    model = glm::scale(model, glm::vec3(rect.size(), 1.0f));

    glActiveTexture(GL_TEXTURE0);
    m_shader.set("image", 0);
    m_shader.set("quadColor", glm::vec4(color, 1.0f));
    m_shader.set("model", model);
    texture.bind();

    // glActiveTexture(GL_TEXTURE0);
    // bind texture
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
