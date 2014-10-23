#include "CTesterGame.h"
#include <iostream>
#include <unistd.h>
#include <csmeg/CDebug.h>

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

void CTesterGame::onDraw(const CGameTime& gameTime) const
{
    LOG_INFO() << "OnRender: " << m_Counter;
    LOG_INFO() << "Elapsed: " << gameTime.getTotalMsec();
}

void CTesterGame::onUpdate(const CGameTime& gameTime)
{
    m_Counter++;
    LOG_INFO() << "OnUpdate: " << m_Counter;
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
    // Game OnInitialize is called before the graphics context and SDL are initialized
    // Resolution etc can be set here.
    setUpdateInterval(300); // msec
    setRenderInterval(1000); // msec

    getGraphicsContext().SetSize(1024, 768);
    return true;
}

void CTesterGame::onRelease()
{
    LOG_INFO() << "Performing Release()";
}
