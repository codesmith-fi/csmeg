#include "CUpdateDispatcher.h"
#include "CGameTime.h"

namespace csmeg {

CUpdateDispatcher::CUpdateDispatcher(int updateFPS) : m_FPS(updateFPS)
{
}

CUpdateDispatcher::~CUpdateDispatcher()
{
}

boost::signals2::connection CUpdateDispatcher::connect(const UpdateNeededSlot &slot)
{
    return m_signalUpdateNeeded.connect(slot);
}

void CUpdateDispatcher::SetFPS(int updateFPS)
{
    m_FPS = (updateFPS <= 0) ? 0 : updateFPS;
    m_UpdateIntervalMsec = 0;
    m_UpdateCounterMsec = 0;
    if( m_FPS > 0 ) {
        m_UpdateIntervalMsec = (int)(1000.0f / (long)updateFPS);
    }

}

void CUpdateDispatcher::Update(const CGameTime& gameTime)
{
    if(NeedsUpdate(gameTime)) {
        OnUpdate(gameTime);
    }
}

void CUpdateDispatcher::OnUpdate(const CGameTime& gameTime)
{
    m_signalUpdateNeeded(gameTime);
}

bool CUpdateDispatcher::NeedsUpdate(const CGameTime& gameTime)
{
    bool result = true;
    if(m_FPS > 0) {
        result = false;
        m_UpdateCounterMsec += gameTime.ElapsedMsec();
        if( m_UpdateCounterMsec >= m_UpdateIntervalMsec ) {
            m_UpdateCounterMsec = 0;
            result = true;
        }
    }
    return result;
}


} // namespace csmeg
