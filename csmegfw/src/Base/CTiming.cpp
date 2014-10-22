#include "CTiming.h"
#include <SDL2/SDL.h>

#include <iostream>

namespace csmeg
{

CTiming::CTiming()
{
    initialize();
}

CTiming::~CTiming()
{
    release();
}

uint32_t CTiming::TicksMsec() const
{
    return (uint32_t)SDL_GetTicks();
}

bool CTiming::onInitialize()
{
    std::cout << "CTiming::OnInitialize()" << std::endl;
    return true;
}

void CTiming::onRelease()
{
    std::cout << "CTiming::OnRelease()" << std::endl;
}

} // namespace csmeg

