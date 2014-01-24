#include "CGraphicsContext.h"
#include "SDL2/SDL.h"
#include "CSmegException.h"
#include <iostream>

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
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_CreateWindowAndRenderer(
        m_Width, m_Height,
        SDL_WINDOW_OPENGL, &window, &renderer);
    SDL_GetRendererInfo(
        m_Renderer, &m_RendererInfo);

    if((m_RendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 ||
        (m_RendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
        std::cerr << "flags: " << m_RendererInfo.flags << std::endl;
        throw CSmegException("Unable to initialize SDL OpenGL Renderer!");
    }

    return false;
}

void CGraphicsContext::OnRelease()
{
}

} // namespace csmeg

