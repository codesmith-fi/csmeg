#include "CTesterGame.h"
#include <iostream>
#include <unistd.h>
#include <CDebug.h>

using namespace std;

CTesterGame::CTesterGame() : m_Counter(0)
{
    LOG_INFO() << "CTesterGame created.";
}

CTesterGame::~CTesterGame()
{
    LOG_INFO() << "CTesterGame destroyed.";
}

void CTesterGame::onLoadContent()
{
    LOG_INFO() << "Performing LoadContent";
}

void CTesterGame::onUnloadContent()
{
    LOG_INFO() << "Performing UnloadContent";
}

void CTesterGame::onDraw() const
{
    getGraphicsContext().clearScreen();
    getGraphicsContext().updateScreen();
}

void CTesterGame::onUpdate(const CGameTime& gameTime)
{
}

void CTesterGame::onEvent(SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN) {
        const SDL_KeyboardEvent& keyEvent = event.key;
        if(keyEvent.state == SDL_PRESSED) {
            LOG_INFO() << "Keypressed: " << keyEvent.keysym.sym;
            if(keyEvent.keysym.sym == SDLK_ESCAPE ) {
                stop();
            }
        }
    }
}

bool CTesterGame::onInitialize()
{
    LOG_INFO() << "Performing Initialize()";

    getGraphicsContext().setSize(1024, 768);
    getGraphicsContext().setFullScreen(true);
    getGraphicsContext().setVsync(true);

    return true;
}

void CTesterGame::onRelease()
{
    LOG_INFO() << "Performing Release()";
}
