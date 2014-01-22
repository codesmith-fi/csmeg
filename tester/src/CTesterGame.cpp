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
    cout << "Elapsed: " << gameTime.Elapsed() << endl;
    sleep(1);
}

void CTesterGame::OnUpdate(const CGameTime& gameTime)
{
    m_Counter++;
    if(m_Counter == 10) {
        Stop();
    }
}

bool CTesterGame::OnInitialize()
{
    return true;
}

void CTesterGame::OnRelease()
{
}
