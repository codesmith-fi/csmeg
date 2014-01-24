#include "CGameTime.h"
#include "CTiming.h"

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
    m_CurrentTicks = m_PreviousTicks = m_StartTicks = CTiming::Instance().TicksMsec();
}

void CGameTime::Update()
{
    m_PreviousTicks = m_CurrentTicks;
    m_CurrentTicks = CTiming::Instance().TicksMsec();
}

uint32_t CGameTime::ElapsedMsec() const
{
    return m_CurrentTicks - m_PreviousTicks;
}

uint32_t CGameTime::TotalMsec() const
{
    return m_CurrentTicks - m_StartTicks;
}

float CGameTime::ElapsedSeconds() const
{
    float msec((float)ElapsedMsec());
    float result(0);

    if(msec > 0.0f) {
        result = 1.0f / msec;
    }
    return result;
}

} // namespace csmeg
