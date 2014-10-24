#ifndef CKEYBOARD_H
#define CKEYBOARD_H

#include <SDL2/SDL_events.h>

namespace csmeg
{

/**
 *
 */
class CKeyboard
{
public: // Constructor and destructor
    CKeyboard();
    ~CKeyboard();
public: // New methods
    bool IsKeyPressed();
    bool IsKeyReleased();
private:
    const Uint8* m_KeyboardStates;
    int m_StatesSize;
};

}

#endif // CKEYBOARD_H
