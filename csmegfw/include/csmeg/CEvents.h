#ifndef CEVENTS_H
#define CEVENTS_H

#include <csmeg/CGameObject.h>
#include <csmeg/MInputEventListener.h>
#include <SDL2/SDL_events.h>
#include <vector>

namespace csmeg
{

class CKeyboard;
class CMouse;
class CJoystick;

class CEvents : public CGameObject
{
    public:
        CEvents();
        virtual ~CEvents();
    protected:
        void OnUpdate(const CGameTime& gameTime);
        bool OnInitialize();

        CKeyboard& Keyboard();
        CMouse& Mouse();
        CJoystick& Joystick();

    private: // New methods
        void HandleKeyboardEvent(SDL_KeyboardEvent& event);
        void HandleMouseMotionEvent(SDL_MouseMotionEvent& event);
    private: // Data
        CKeyboard* m_Keyboard;
        CMouse* m_Mouse;
        CJoystick* m_Joystick;

        MInputEventListener<SDL_KeyboardEvent>* m_keyboardListener;
        MInputEventListener<SDL_KeyboardEvent>* m_mouseMotionListener;
};

} // namespace csmeg
#endif // CEVENTS_H
