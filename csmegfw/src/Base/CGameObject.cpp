#include "CGameObject.h"
#include <CGameTime.h>
#include <boost/bind.hpp>

namespace csmeg
{

CGameObject::CGameObject() : m_Updater(0)
{
    m_UpdaterConnection = m_Updater.connect(boost::bind(&CGameObject::ProcessUpdate, this, _1));
}

CGameObject::~CGameObject()
{
    m_UpdaterConnection.disconnect();
}

void CGameObject::Update(const CGameTime& gameTime)
{
    if(m_Updater.FPS() > 0) {
        m_Updater.Update(gameTime);
    } else {
        ProcessUpdate(gameTime);
    }
}

void CGameObject::ProcessUpdate(const CGameTime& gameTime)
{
    OnUpdate(gameTime);
}

void CGameObject::SetUpdateFPS(int fps)
{
    m_Updater.SetFPS(fps);
}

int CGameObject::UpdateFPS() const
{
    return m_Updater.FPS();
}

} // namespace csmeg

