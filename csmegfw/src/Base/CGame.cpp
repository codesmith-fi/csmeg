#include "CGame.h"
#include "CTiming.h"
#include <iostream>
#include <SDL2/SDL.h>

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

bool CGame::Initialize()
{
    if(SDL_Init(0) != 0) {
        cout << "Error initializing SDL" << endl;
        return false;
    }

    CTiming::Instance();

/*
    cout << "Init SDL Timer" << endl;
    if(SDL_InitSubSystem(SDL_INIT_TIMER) != 0) {
        cerr << "SDL Timer, failed" << endl;
        return false;
    }
*/
    cout << "Init SDL Audio" << endl;
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        cerr << "SDL Audio, failed" << endl;
        return false;
    }

    cout << "Init SDL Video" << endl;
    if(SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL Video, failed" << endl;
        return false;
    }

    m_IsInitialized = CGameObject::Initialize();
    return m_IsInitialized;
}

void CGame::Release()
{
    SDL_Quit();
}

} // namespace csmeg
