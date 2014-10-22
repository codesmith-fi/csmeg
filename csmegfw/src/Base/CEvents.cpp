#include "CEvents.h"
#include "CKeyboard.h"
#include "CMouse.h"
#include "CJoystick.h"
#include "CSmegException.h"
#include "SDL2/SDL_events.h"

namespace csmeg
{

CEvents::CEvents()
{
    m_eventListener = NULL;
}

CEvents::~CEvents()
{
}

void CEvents::AddEventListener(MInputEventListener* listener)
{
    m_eventListener = listener;
}

void CEvents::Update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(m_eventListener != NULL) {
            m_eventListener->OnEvent(event);
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
