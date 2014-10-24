#include "CGraphicsContext.h"
#include "CSmegException.h"

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
    FreeContext();
}

void CGraphicsContext::SetSize(int X, int Y)
{
    m_Width = X;
    m_Height = Y;
}

bool CGraphicsContext::onInitialize()
{
	m_Window = SDL_CreateWindow("My Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_Width, m_Height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	m_GLContext = SDL_GL_CreateContext(m_Window);
	if (m_GLContext == NULL)
	{
		throw CSmegException("There was an error creating the OpenGL context!\n");
	}

	const unsigned char *version = glGetString(GL_VERSION);
	if (version == NULL)
	{
		throw CSmegException("There was an error creating the OpenGL context!\n");
	}

	SDL_GL_MakeCurrent(m_Window, m_GLContext);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	glewExperimental = GL_TRUE;
	GLenum glew_status = glewInit();
	if (glew_status != 0)
    {
        std::string errstr( (const char*)glewGetErrorString(glew_status) );
		throw CSmegException(errstr);
    }

    // Vsync - 0 = disabled
//    SDL_GL_SetSwapInterval(1);

    initOpenGL();

    return false;
}

void CGraphicsContext::onRelease()
{
    FreeContext();
}

void CGraphicsContext::FreeContext()
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


