#ifndef MINPUTEVENTLISTENER_H
#define MINPUTEVENTLISTENER_H

#include <SDL2/SDL_events.h>

namespace csmeg
{

class MInputEventListener
{
    public:
        virtual void OnEvent(SDL_Event& event) = 0;
};

}
#endif // MINPUTEVENTLISTENER_H
