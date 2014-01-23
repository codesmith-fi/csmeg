#include "CGameObject.h"
#include <CGameTime.h>
#include <inttypes.h>

namespace csmeg
{

CGameObject::CGameObject() : m_FPS(FPSUnlimited)
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::Update(const CGameTime& gameTime)
{
    if(NeedsUpdate(gameTime)) {
        OnUpdate(gameTime);
    }
}

bool CGameObject::Initialize()
{
    return OnInitialize();
}

void CGameObject::Release()
{
    return OnRelease();
}

void CGameObject::SetFPS(int fps)
{
    m_FPS = fps <= 0 ? FPSUnlimited : fps;
    m_UpdateIntervalMsec = 0;
    m_UpdateCounterMsec = 0;
    if( m_FPS > FPSUnlimited ) {
        m_UpdateIntervalMsec = 1.0l / (long)m_FPS;
    }
}

int CGameObject::FPS() const
{
    return m_FPS;
}

bool CGameObject::NeedsUpdate(const CGameTime& gameTime)
{
    bool result = true;
    if(m_FPS != FPSUnlimited) {
        result = false;
        m_UpdateCounterMsec += gameTime.Elapsed();
        if( m_UpdateCounterMsec >= m_UpdateIntervalMsec ) {
            m_UpdateCounterMsec = 0;
            result = true;
        }
    }
    return result;
}

} // namespace csmeg

