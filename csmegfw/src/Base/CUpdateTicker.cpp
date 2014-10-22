#include "CUpdateTicker.h"
#include "CGameTime.h"

using namespace csmeg;

CUpdateTicker::CUpdateTicker(int intervalMsec) :
    m_UpdateInterval(intervalMsec > 0 ? intervalMsec : CSMEG_DEFAULT_UPDATE_INTERVAL_MSEC),
    m_UpdateCounter(0),
    m_FPS(intervalMsec / 1000.0f)
{
}

CUpdateTicker::~CUpdateTicker()
{
}

void CUpdateTicker::setUpdateInterval(int msec)
{
    msec = (msec <= 0) ? CSMEG_DEFAULT_UPDATE_INTERVAL_MSEC : msec;

    m_FPS = (msec <= 0) ? 0 : msec / 1000.0f;
    m_UpdateInterval = msec;
}

int CUpdateTicker::getUpdateInterval() const
{
    return m_UpdateInterval;
}

bool CUpdateTicker::tick(const CGameTime& gameTime)
{
    bool result = false;
    m_UpdateCounter += gameTime.ElapsedMsec();
    if( m_UpdateCounter >= m_UpdateInterval ) {
        m_UpdateCounter = 0;
        result = true;
    }
    return result;
}
