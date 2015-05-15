#ifndef CTESTERGAME_H
#define CTESTERGAME_H

#include <CGame.h>
#include <Texture2D.h>
#include <SDL2/SDL_events.h>
#include <memory>

using namespace csmeg;
using renderer::Texture2D;

class CTesterGame : public CGame
{
    public:
        CTesterGame();
        ~CTesterGame();
    protected:

    private: // From Base
        void onDraw() const;
        void onUpdate(const CGameTime& gameTime);
        bool onInitialize();
        void onRelease();
        void onEvent(SDL_Event& event);
        void onLoadContent();
        void onUnloadContent();

    private: // Data
        int m_Counter;
        std::shared_ptr<renderer::Texture2D> m_texture;

};

#endif // CTESTERGAME_H
