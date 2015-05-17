#include "CGraphicsContext.h"
#include "TRectangle.h"
#include "CSmegException.h"
#include "CDebug.h"

#include "CShaderProgram.h"
#include "CShader.h"
#include "ContentManager.h"
#include "TCamera2D.h"

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
}

void CGraphicsContext::updateScreen()
{
    SDL_GL_SwapWindow(m_Window);
}

renderer::CRenderBatch& CGraphicsContext::DefaultRenderer()
{
    return *m_batchRenderer.get();
}

void CGraphicsContext::updateView(const glm::mat4& viewMatrix)
{
    m_viewMatrix = viewMatrix;
    m_quadRenderer->setView(viewMatrix);
}

bool CGraphicsContext::onInitialize()
{
    LOG_INFO() << "CGraphicsContext::onInitialize()";

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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, m_VSyncEnabled ? 1 : 0);
    SDL_GL_SetSwapInterval(m_VSyncEnabled ? 1 : 0);

    glewExperimental = GL_TRUE;
    GLenum glew_status = glewInit();
    if(glew_status != GLEW_OK) {
        std::string errstr((const char*)glewGetErrorString(glew_status));
        throw CSmegException(errstr);
    }

    glClearColor(m_backgroundColor.red(), m_backgroundColor.green(), m_backgroundColor.blue(), m_backgroundColor.alpha());
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_viewMatrix = TCamera2D(
        TVector2(0,0),
        TVector2(m_Width*0.5f, m_Height*0.5f),
        0,
        1.0f
        ).get();

    m_projectionMatrix = glm::ortho(
        0.0f,
        static_cast<GLfloat>(m_Width),
        static_cast<GLfloat>(m_Height),
        0.0f,
        -1.0f,
        1.0f);

    ShaderProgramPtr shader(new CShaderProgram());
    shader->add(std::make_unique<CShader>(CShader::SHADER_TYPE::Vertex, std::string("quadshader.v")));
    shader->add(std::make_unique<CShader>(CShader::SHADER_TYPE::Fragment, std::string("quadshader.f")));
    shader->link();

    m_quadRenderer.reset(new CQuadRenderer());
    m_quadRenderer->setShaderProgram(shader);

    m_quadRenderer->setProjection(m_projectionMatrix);

    m_batchRenderer.reset(new CRenderBatch());
    m_batchRenderer->setRenderer(m_quadRenderer);
    updateView(m_viewMatrix);

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


