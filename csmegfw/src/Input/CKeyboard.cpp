#include "CKeyboard.h"
#include <SDL2/SDL_events.h>

namespace csmeg
{

CKeyboard::CKeyboard()
{
    m_KeyboardStates = SDL_GetKeyboardState(&m_StatesSize);
}

CKeyboard::~CKeyboard()
{
}

}
