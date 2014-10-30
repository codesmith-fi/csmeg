#include "CEvents.h"
#include "CKeyboard.h"
#include "CMouse.h"
#include "CJoystick.h"
#include "CSmegException.h"
#include "SDL2/SDL_events.h"

namespace csmeg
{

CEvents::CEvents() : m_eventListener(nullptr)
{
}

CEvents::~CEvents()
{
}

void CEvents::addEventListener(MInputEventListener* listener)
{
    m_eventListener = listener;
}

void CEvents::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(m_eventListener != NULL) {
            m_eventListener->onEvent(event);
        }
    }
}

bool CEvents::onInitialize()
{
    return true;
}

void CEvents::onRelease()
{
}

} // namespace csmeg
