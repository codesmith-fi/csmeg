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
    //dtor
}

void CTesterGame::OnDraw(const CGameTime& gameTime) const
{
    cout << "OnRender: " << m_Counter << endl;
    cout << "Elapsed: " << gameTime.TotalMsec() << endl;
//    usleep(12*1000);
}

void CTesterGame::OnUpdate(const CGameTime& gameTime)
{
    m_Counter++;

    cout << "OnUpdate: " << m_Counter << endl;
/*
    if(m_Counter == 10) {
        Stop();
    }
*/
}

void CTesterGame::OnEvent(SDL_KeyboardEvent& event)
{
    if(event.state == SDL_PRESSED) {
        cout << "Keypressed: " << event.keysym.sym << endl;
        if(event.keysym.sym == SDLK_ESCAPE ) {
            Stop();
        }
    }
}

bool CTesterGame::OnInitialize()
{
    SetUpdateFPS(20);
    Events().AddKeyboardListener(this);
    return true;
}

void CTesterGame::OnRelease()
{
    cout << "OnRelease" << endl;
}
