#include "CGraphicsContext.h"
#include "CSmegException.h"
#include "CDebug.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

using namespace csmeg;

namespace {
    void initOpenGL()
    {

    }
}

CGraphicsContext::CGraphicsContext() : CGraphicsContext(0, 0)
{
}

CGraphicsContext::CGraphicsContext(int X, int Y)
    : m_Window(nullptr), m_GLContext(nullptr), m_Width(X), m_Height(Y)
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

void CGraphicsContext::setFullScreen(bool enabled)
{
}

void CGraphicsContext::setVsync(bool enabled)
{
    // Vsync - 0 = disabled
    SDL_GL_SetSwapInterval( enabled ? 1 : 0 );
}

void CGraphicsContext::clearScreen()
{
    LOG_INFO() << "CGraphicsContext::clearScreen()";

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void CGraphicsContext::updateScreen()
{
    SDL_GL_SwapWindow(m_Window);
}

bool CGraphicsContext::onInitialize()
{
    LOG_INFO() << "CGraphicsContext::onInitialize()";
	m_Window = SDL_CreateWindow("My Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_Width, m_Height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if( m_Window == nullptr ) {
        throw CSmegException("Could not initialize SDL2 Window");
    }

	m_GLContext = SDL_GL_CreateContext(m_Window);
	if (m_GLContext == nullptr)	{
		throw CSmegException("There was an error creating the OpenGL context!\n");
	}

	const unsigned char *version = glGetString(GL_VERSION);
	if (version == nullptr)	{
		throw CSmegException("There was an error creating the OpenGL context!\n");
	}

	LOG_INFO() << "OpenGL Version: " << version;

	SDL_GL_MakeCurrent(m_Window, m_GLContext);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	glewExperimental = GL_TRUE;
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
        std::string errstr( (const char*)glewGetErrorString(glew_status) );
		throw CSmegException(errstr);
    }

    initOpenGL();

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


