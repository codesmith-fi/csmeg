#include "CGraphicsContext.h"
#include "CSmegException.h"
#include "CDebug.h"

#include "CShaderProgram.h"
#include "CShader.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
//#include <glm/gtc/matrix_transform.hpp>

using namespace csmeg;
using namespace csmeg::renderer;

CGraphicsContext::CGraphicsContext() : CGraphicsContext(0, 0)
{
}

CGraphicsContext::CGraphicsContext(int X, int Y)
    : m_Window(nullptr), m_GLContext(nullptr), m_Width(X), m_Height(Y), m_VSyncEnabled(true)
{
}


CGraphicsContext::~CGraphicsContext()
{
    freeContext();
}

void CGraphicsContext::setSize(int X, int Y)
{
    m_Width = X;
    m_Height = Y;
}

void CGraphicsContext::setBackgroundColor(const Color& color)
{
    m_backgroundColor = color;
}

void CGraphicsContext::setFullScreen(bool enabled)
{
    LOG_WARN() << "setFullScreen() not implemented yet";
}

void CGraphicsContext::setVsync(bool enabled)
{
    // Vsync - 0 = disabled
    m_VSyncEnabled = enabled;
}

void CGraphicsContext::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // temporary code
    // Use our shader
    m_shaderProgram->use();
    
    m_shaderProgram->setUniform("uColor", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);

    // temporary code
}

void CGraphicsContext::updateScreen()
{
    SDL_GL_SwapWindow(m_Window);
}

bool CGraphicsContext::onInitialize()
{
    LOG_INFO() << "CGraphicsContext::onInitialize()";

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, m_VSyncEnabled ? 1 : 0);
    SDL_GL_SetSwapInterval(m_VSyncEnabled ? 1 : 0);

    m_Window = SDL_CreateWindow("CSMEG Tester",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_Width, m_Height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_Window == nullptr) {
        throw CSmegException("Could not initialize SDL2 Window");
    }

    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_GLContext = SDL_GL_CreateContext(m_Window);
    if(m_GLContext == nullptr) {
        throw CSmegException("There was an error creating the OpenGL context!\n");
    }

    const unsigned char *version = glGetString(GL_VERSION);
    if(version == nullptr) {
        throw CSmegException("There was an error creating the OpenGL context!\n");
    }

    LOG_INFO() << "OpenGL Version: " << version;

    SDL_GL_MakeCurrent(m_Window, m_GLContext);

    glewExperimental = GL_TRUE;
    GLenum glew_status = glewInit();
    if(glew_status != GLEW_OK) {
        std::string errstr((const char*)glewGetErrorString(glew_status));
        throw CSmegException(errstr);
    }

    glClearColor(m_backgroundColor.red(), m_backgroundColor.green(), m_backgroundColor.blue(), m_backgroundColor.alpha());

    m_shaderProgram.reset(new CShaderProgram());
    m_shaderProgram->add(std::make_unique<CShader>(CShader::SHADER_TYPE::Vertex, std::string("colorflat.v")));
    m_shaderProgram->add(std::make_unique<CShader>(CShader::SHADER_TYPE::Fragment, std::string("colorflat.f")));
    m_shaderProgram->link();

    //glm::ortho<GLfloat>(0.0, m_Width, m_Height, 0.0, 0, -1.0);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    return false;
}

void CGraphicsContext::onRelease()
{
    LOG_INFO() << "CGraphicsContext::onRelease()";
    freeContext();
}

void CGraphicsContext::freeContext()
{
    if(m_GLContext) {
        SDL_GL_DeleteContext(m_GLContext);
        m_GLContext = nullptr;
    }

    if(m_Window) {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }
}


