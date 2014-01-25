#include "CGame.h"
#include "CGraphicsContext.h"
#include "CTiming.h"
#include "CEvents.h"

#include "CSmegException.h"

#include <iostream>
#include <SDL2/SDL.h>

namespace csmeg
{

using namespace std;

CGame::CGame()
    : m_IsRunning(false),
      m_MinimumUpdateInterval(10)
{
    m_GraphicsContext = new CGraphicsContext();
    m_Events = new CEvents();
    m_GameTime = new CGameTime();

    cout << "CGame created" << endl;
}

CGame::~CGame()
{
    m_IsRunning = false;
    Release();

    delete m_GameTime;
    delete m_Events;
    delete m_GraphicsContext;

}

void CGame::Run()
{
    if(Initialize()) {
        m_IsRunning = true;
        m_GameTime->Reset();

        while(m_IsRunning) {
            Update(*m_GameTime);
            Draw(*m_GameTime);

            m_GameTime->Update();
            m_Events->Update();

            // Do not allow game loop to take 100% CPU, limit update loop speed
            int diff(m_MinimumUpdateInterval - m_GameTime->ElapsedMsec());
            if( diff > 0 ) {
                SDL_Delay(diff);
            }
        }
    }
    Release();
}

void CGame::Stop()
{
    m_IsRunning = false;
}

CGraphicsContext& CGame::GraphicsContext() const
{
    if( !IsInitialized() ) {
        throw CSmegException("Game is not initialized");
    }
    return *m_GraphicsContext;
}

bool CGame::Initialize()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "Error initializing SDL" << endl;
        return false;
    }

    CTiming::Instance();

    m_GraphicsContext->Initialize();

    return CGameObject::Initialize();
}

void CGame::Release()
{
    m_GraphicsContext->Release();
    SDL_Quit();
}

} // namespace csmeg
