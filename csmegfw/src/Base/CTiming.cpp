#include "CTiming.h"
#include <SDL2/SDL.h>

#include <iostream>

namespace csmeg
{

CTiming::CTiming()
{
}

CTiming::~CTiming()
{
}

uint32_t CTiming::TicksMsec()
{
    return SDL_GetTicks();
}

void CTiming::DelayMsec(uint32_t waitMsec)
{
    SDL_Delay(waitMsec);
}

} // namespace csmeg

