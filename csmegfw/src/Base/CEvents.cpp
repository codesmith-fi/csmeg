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
    m_Mouse = NULL;
    m_Keyboard = NULL;
    m_Joystick = NULL;
    m_keyboardListener = NULL;
}

CEvents::~CEvents()
{
    delete m_Mouse;
    delete m_Keyboard;
    delete m_Joystick;
}

void CEvents::AddKeyboardListener(MInputEventListener<SDL_KeyboardEvent>* listener)
{
    m_keyboardListener = listener;
}

CKeyboard& CEvents::Keyboard()
{
    if(!IsInitialized())
    {
        throw CSmegException("CEvents is Uninitialized");
    }
    return *m_Keyboard;
}

CMouse& CEvents::Mouse()
{
    if(!IsInitialized())
    {
        throw CSmegException("CEvents is Uninitialized");
    }
    return *m_Mouse;
}

CJoystick& CEvents::Joystick()
{
    if(!IsInitialized())
    {
        throw CSmegException("CEvents is Uninitialized");
    }
    return *m_Joystick;
}

void CEvents::Update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
        {
            break;
        }
        case SDL_KEYUP:
        case SDL_KEYDOWN:
        {
            HandleKeyboardEvent(event.key);
            break;
        }
        case SDL_MOUSEMOTION:
            HandleMouseMotionEvent(event.motion);
        default:
        {

        }
            // uninteresting event
        }
    }
}

void CEvents::HandleKeyboardEvent(SDL_KeyboardEvent& event)
{
    if(m_keyboardListener != NULL) {
        m_keyboardListener->OnEvent(event);
    }
}

void CEvents::HandleMouseMotionEvent(SDL_MouseMotionEvent& event)
{
}


bool CEvents::OnInitialize()
{
    m_Keyboard = new CKeyboard();
    m_Mouse = new CMouse();
    m_Joystick = new CJoystick();
    return true;
}

void CEvents::OnRelease()
{
}

} // namespace csmeg
