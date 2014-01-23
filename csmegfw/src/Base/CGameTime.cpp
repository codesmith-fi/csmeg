#include "CGameTime.h"
#include <SDL2/SDL_timer.h>

namespace csmeg
{

CGameTime::CGameTime()
{
    Reset();
}

CGameTime::~CGameTime()
{
}

CGameTime::CGameTime(const CGameTime& other)
{
    m_CurrentTicks = other.m_CurrentTicks;
    m_PreviousTicks = other.m_PreviousTicks;
    m_StartTicks = other.m_StartTicks;
}

CGameTime& CGameTime::operator=(const CGameTime& rhs)
{
    // handle self assignment
    if(this != &rhs) {
        m_CurrentTicks = rhs.m_CurrentTicks;
        m_PreviousTicks = rhs.m_PreviousTicks;
        m_StartTicks = rhs.m_StartTicks;
    }

    return *this;
}

CGameTime& CGameTime::operator+=(const CGameTime& rhs)
{
    m_CurrentTicks+=rhs.m_CurrentTicks;
    return *this;
}

CGameTime& CGameTime::operator-=(const CGameTime& rhs)
{
    m_CurrentTicks-=rhs.m_CurrentTicks;
    return *this;
}


void CGameTime::Reset()
{
    m_CurrentTicks = m_PreviousTicks = m_StartTicks = SDL_GetTicks();
}

void CGameTime::Update()
{
    m_PreviousTicks = m_CurrentTicks;
    m_CurrentTicks = SDL_GetTicks();
}

uint32_t CGameTime::Elapsed() const
{
    return m_CurrentTicks - m_PreviousTicks;
}

uint32_t CGameTime::Total() const
{
    return m_CurrentTicks - m_StartTicks;
}

} // namespace csmeg
