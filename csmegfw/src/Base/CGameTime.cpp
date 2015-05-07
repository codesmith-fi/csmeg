#include "CGameTime.h"
#include "CTiming.h"

namespace csmeg
{

CGameTime::CGameTime() : m_StartTicks(0), m_CurrentTicks(0), m_PreviousTicks(0)
{
    reset();
}

CGameTime::~CGameTime()
{
}

CGameTime::CGameTime(const CGameTime& other) :
    m_StartTicks(other.m_StartTicks),
    m_CurrentTicks(other.m_CurrentTicks),
    m_PreviousTicks(other.m_PreviousTicks)
{
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


void CGameTime::reset()
{
    m_CurrentTicks = m_PreviousTicks = m_StartTicks = CTiming::TicksMsec();
}

void CGameTime::update()
{
    m_PreviousTicks = m_CurrentTicks;
    m_CurrentTicks = CTiming::TicksMsec();
}

uint32_t CGameTime::getElapsedMsec() const
{
    return m_CurrentTicks - m_PreviousTicks;
}

uint32_t CGameTime::getTotalMsec() const
{
    return m_CurrentTicks - m_StartTicks;
}

float CGameTime::getElapsedSeconds() const
{
    float msec(static_cast<float>(getElapsedMsec()));
    float result(0.0f);

    if(msec > 0.0f) {
        result = 1.0f / msec;
    }
    return result;
}

} // namespace csmeg
