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
      m_GameIsSetup(false),
      m_MinimumUpdateInterval(10)
{
    m_GameTime = NULL;
    m_Events = NULL;
    m_GraphicsContext = NULL;
}

CGame::~CGame()
{
    Release();

    delete m_GameTime;
    delete m_Events;
    delete m_GraphicsContext;
}

void CGame::Run()
{
    // Setup the needed frameworks, e.g. SDL
    SetupGame();

    // Call init for our Gameobject, causes OnInititialize() on derived
    // came objects
    if(Initialize()) {
        m_IsRunning = true;
        m_GameTime->Reset();

        while(m_IsRunning) {
            Update(*m_GameTime);
            Draw(*m_GameTime);

            m_Events->Update();
            m_GameTime->Update();

            // Do not allow game loop to take 100% CPU, limit update loop speed
            int diff(m_MinimumUpdateInterval - m_GameTime->ElapsedMsec());
            if( diff > 0 ) {
                SDL_Delay(diff);
            }
        }
    }
    Release();
    FreeGame();
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

void CGame::OnEvent(SDL_Event& event)
{
}


void CGame::SetupGame()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw CSmegException(SDL_GetError());
    }

    CTiming::Instance();

    m_GraphicsContext = new CGraphicsContext();

    m_Events = new CEvents();
    m_Events->AddEventListener(this);

    m_GameTime = new CGameTime();

    m_GraphicsContext->Initialize();
    m_GameIsSetup = true;
}

void CGame::FreeGame()
{
    if(m_GameIsSetup) {
        if( m_GraphicsContext != NULL ) {
            m_GraphicsContext->Release();
        }
        SDL_Quit();

        m_GameIsSetup = false;
    }
}

} // namespace csmeg
