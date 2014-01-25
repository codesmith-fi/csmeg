#include "CTiming.h"
#include <SDL2/SDL.h>

#include <iostream>

namespace csmeg
{

CTiming::CTiming()
{
    Initialize();
}

CTiming::~CTiming()
{
    Release();
}

uint32_t CTiming::TicksMsec() const
{
    return (uint32_t)SDL_GetTicks();
}

bool CTiming::OnInitialize()
{
    std::cout << "CTiming::OnInitialize()" << std::endl;
    return true;
}

void CTiming::OnRelease()
{
    std::cout << "CTiming::OnRelease()" << std::endl;
}

} // namespace csmeg

