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
        Release();
    }
}

void CGame::Run()
{
    if(Initialize()) {
        m_IsRunning = true;
        m_GameTime.Reset();

        while(m_IsRunning) {
            m_GameTime.Update();
            Update(m_GameTime);
            Draw(m_GameTime);
        }
    }
    Release();
}

void CGame::Stop()
{
    m_IsRunning = false;
}

void CGame::Draw(const CGameTime& gameTime) const
{
    OnDraw(gameTime);
}

void CGame::Update(const CGameTime& gameTime)
{
    OnUpdate(gameTime);
}

bool CGame::Initialize()
{
    m_IsInitialized = OnInitialize();
    return m_IsInitialized;
}

void CGame::Release()
{
    m_IsInitialized = false;
    return OnRelease();
}

} // namespace csmeg
