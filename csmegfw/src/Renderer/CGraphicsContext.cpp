#include "CGraphicsContext.h"
#include "TRectangle.h"
#include "CSmegException.h"
#include "CDebug.h"

#include "CShaderProgram.h"
#include "CShader.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    glm::vec2 pos(200.0f, 100.f);
    for(int i = 0; i < 5; i++) {
        m_quadRenderer->render(m_texture, pos, glm::vec2(50.0f, 50.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        pos.x += 50.0f;
        pos.y += 50.0f;
    }
}

void CGraphicsContext::updateScreen()
{
    SDL_GL_SwapWindow(m_Window);
}

void CGraphicsContext::drawRectangle(const TRectangle& rect, const Color& color)
{
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

    glm::mat4 projection = glm::ortho(
        0.0f,
        static_cast<GLfloat>(m_Width),
        static_cast<GLfloat>(m_Height),
        0.0f,
        -1.0f,
        1.0f);

    m_shaderProgram->use();
    m_shaderProgram->set("projection", projection);

    m_quadRenderer = new CQuadRenderer(*m_shaderProgram);

//    m_texture.load("jupiter.png");

    // Black/white checkerboard
    float pixels[] = {
        1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
    };
    
    m_texture.generate(2, 2, pixels);

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


