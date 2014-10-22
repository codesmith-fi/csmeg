#ifndef CTESTERGAME_H
#define CTESTERGAME_H

#include <csmeg/CGame.h>
#include <SDL2/SDL_events.h>

using namespace csmeg;

class CTesterGame : public CGame
{
    public:
        CTesterGame();
        ~CTesterGame();
    protected:

    private: // From Base
        void onDraw(const CGameTime& gameTime) const;
        void onUpdate(const CGameTime& gameTime);
        bool onInitialize();
        void onRelease();
        void onEvent(SDL_Event& event);
        void onLoadContent();
        void onUnloadContent();

    private: // Data
        int m_Counter;
};

#endif // CTESTERGAME_H
