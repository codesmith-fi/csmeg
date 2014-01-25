#include "CGraphicsContext.h"
#include "CSmegException.h"

#include "GL/glew.h"
#include "SDL2/SDL.h"

namespace csmeg
{

CGraphicsContext::CGraphicsContext() : m_Width(DefaultWindowWidth), m_Height(DefaultWindowHeight)
{
}

CGraphicsContext::CGraphicsContext(int width, int height)
    : m_Width(width), m_Height(height)
{
}


CGraphicsContext::~CGraphicsContext()
{
}

bool CGraphicsContext::OnInitialize()
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

	glewExperimental = GL_TRUE;
	GLenum glew_status = glewInit();
	if (glew_status != 0)
    {
        std::string errstr( (const char*)glewGetErrorString(glew_status) );
		throw CSmegException(errstr);
    }

    return false;
}

void CGraphicsContext::OnRelease()
{
}

} // namespace csmeg

