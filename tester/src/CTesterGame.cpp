#include "CTesterGame.h"
#include <iostream>
#include <unistd.h>

using namespace std;

CTesterGame::CTesterGame() : m_Counter(0)
{
    cout << "CTesterGame created" << endl;
}

CTesterGame::~CTesterGame()
{
}

void CTesterGame::onLoadContent()
{
}

void CTesterGame::onUnloadContent()
{
}

void CTesterGame::onDraw(const CGameTime& gameTime) const
{
    cout << "OnRender: " << m_Counter << endl;
    cout << "Elapsed: " << gameTime.TotalMsec() << endl;
}

void CTesterGame::onUpdate(const CGameTime& gameTime)
{
    m_Counter++;
    cout << "OnUpdate: " << m_Counter << endl;
}

void CTesterGame::OnEvent(SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN) {
        const SDL_KeyboardEvent& keyEvent = event.key;
        if(keyEvent.state == SDL_PRESSED) {
            cout << "Keypressed: " << keyEvent.keysym.sym << endl;
            if(keyEvent.keysym.sym == SDLK_ESCAPE ) {
                Stop();
            }
        }
    }
}

bool CTesterGame::onInitialize()
{
    // Game OnInitialize is called before the graphics context and SDL are initialized
    // Resolution etc can be set here.
    setUpdateInterval(300); // msec
    setRenderInterval(1000); // msec

    GraphicsContext().SetSize(1024, 768);
    return true;
}

void CTesterGame::onRelease()
{
    cout << "OnRelease" << endl;
}
