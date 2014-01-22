#include "CGame.h"

#include <iostream>

namespace csmeg
{

using namespace std;

CGame::CGame() : m_IsRunning(false), m_IsInitialized(false)
{
    cout << "CGame created" << endl;
}

CGame::~CGame()
{
    if(m_IsInitialized) {
        m_IsRunning = false;
        OnRelease();
    }
}

void CGame::Run()
{
    if(OnInitialize()) {
        m_IsInitialized = true;
        m_IsRunning = true;
        m_GameTime.Reset();

        while(m_IsRunning) {
            m_GameTime.Update();
            OnUpdate(m_GameTime);
            OnRender(m_GameTime);
        }
    }
    OnRelease();
}

void CGame::Stop()
{
    m_IsRunning = false;
}

void CGame::OnRender(const CGameTime& gameTime) const
{
}

void CGame::OnUpdate(const CGameTime& gameTime)
{
}

bool CGame::OnInitialize()
{
    return true;
}

void CGame::OnRelease()
{
    if(m_IsInitialized) {
        m_IsInitialized = false;
    }
}

} // namespace csmeg
