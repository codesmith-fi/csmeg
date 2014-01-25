#ifndef CTESTERGAME_H
#define CTESTERGAME_H

#include <csmeg/CGame.h>
#include <csmeg/MInputEventListener.h>
#include <SDL2/SDL_events.h>

using namespace csmeg;

class CTesterGame : public CGame, public MInputEventListener<SDL_KeyboardEvent>
{
    public:
        CTesterGame();
        ~CTesterGame();
    protected:

    private: // From Base
        void OnDraw(const CGameTime& gameTime) const;
        void OnUpdate(const CGameTime& gameTime);
        bool OnInitialize();
        void OnRelease();
    private: // From  MInputEventListener
        void OnEvent(SDL_KeyboardEvent& event);

    private: // Data
        int m_Counter;
};

#endif // CTESTERGAME_H
