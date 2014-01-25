#ifndef CEVENTS_H
#define CEVENTS_H

#include <csmeg/CObjectBase.h>
#include <csmeg/MInputEventListener.h>
#include <SDL2/SDL_events.h>
#include <vector>

namespace csmeg
{

class CKeyboard;
class CMouse;
class CJoystick;

class CEvents : public CObjectBase
{
    public:
        CEvents();
        virtual ~CEvents();
    public: // New methods
        void Update();
        void AddKeyboardListener(MInputEventListener<SDL_KeyboardEvent>* listener);

        CKeyboard& Keyboard();
        CMouse& Mouse();
        CJoystick& Joystick();

    protected: // From CObjectBase
        bool OnInitialize();
        void OnRelease();

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
