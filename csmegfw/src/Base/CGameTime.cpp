#include "CGameTime.h"

namespace csmeg
{

CGameTime::CGameTime()
{
    Reset();
}

CGameTime::~CGameTime()
{
    //dtor
}

CGameTime::CGameTime(const CGameTime& other)
{
    //copy ctor
}

CGameTime& CGameTime::operator=(const CGameTime& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
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

Uint32 CGameTime::Elapsed() const
{
    return m_CurrentTicks - m_PreviousTicks;
}

Uint32 CGameTime::Total() const
{
    return m_CurrentTicks - m_StartTicks;
}

} // namespace csmeg
