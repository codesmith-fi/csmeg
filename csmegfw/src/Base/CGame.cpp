#include "CGame.h"
#include "CGraphicsContext.h"
#include "CTiming.h"
#include "CEvents.h"

#include "CSmegException.h"
#include "CDebug.h"

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
    m_GraphicsContext = new CGraphicsContext();
    m_Events = new CEvents();
    m_GameTime = new CGameTime();
}

CGame::~CGame()
{
    release();

    delete m_GameTime;
    delete m_Events;
    delete m_GraphicsContext;
}

void CGame::run()
{
    // Call init for our Gameobject, causes OnInititialize() on derived
    // came objects
    if(initialize()) {

        // Setup the needed frameworks, e.g. SDL
        setupGame();
        loadContent();

        m_IsRunning = true;
        m_GameTime->reset();

        while(m_IsRunning) {
            update(*m_GameTime);
            draw(*m_GameTime);

            m_Events->update();
            m_GameTime->update();

            // Do not allow game loop to take 100% CPU, limit update loop speed
            int diff(m_MinimumUpdateInterval - m_GameTime->getElapsedMsec());
            if( diff > 0 ) {
                SDL_Delay(diff);
            }
        }
    }

    unloadContent();
    release();
    freeGame();
}

void CGame::stop()
{
    m_IsRunning = false;
}

CGraphicsContext& CGame::getGraphicsContext() const
{
    return *m_GraphicsContext;
}

void CGame::onEvent(SDL_Event& /* event */)
{
}

void CGame::setupGame()
{
    LOG_INFO() << "CGame::setupGame()";
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw CSmegException(SDL_GetError());
    }

    CTiming::Instance();

    m_Events->addEventListener(this);
    m_GraphicsContext->initialize();
    m_GameIsSetup = true;
}

void CGame::freeGame()
{
    LOG_INFO() << "CGame::freeGame()";
    if(m_GameIsSetup) {
        if( m_GraphicsContext != NULL ) {
            m_GraphicsContext->release();
        }
        SDL_Quit();

        m_GameIsSetup = false;
    }
}

} // namespace csmeg
