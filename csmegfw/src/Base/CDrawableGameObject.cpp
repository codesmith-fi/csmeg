#include "CDrawableGameObject.h"
#include <boost/bind.hpp>

namespace csmeg
{

CDrawableGameObject::CDrawableGameObject() : m_DrawUpdater(0)
{
    m_DrawUpdaterConnection = m_DrawUpdater.connect(boost::bind(&CDrawableGameObject::ProcessUpdate, this, _1));
}

CDrawableGameObject::~CDrawableGameObject()
{
    m_DrawUpdaterConnection.disconnect();
}

void CDrawableGameObject::Draw(const CGameTime& gameTime) const
{
    CDrawableGameObject* obj = const_cast<CDrawableGameObject*>(this);
    if( m_DrawUpdater.FPS() > 0 ) {
        obj->m_DrawUpdater.Update(gameTime);
    } else {
        obj->ProcessUpdate(gameTime);
    }
}

void CDrawableGameObject::SetDrawFPS(int fps)
{
    m_DrawUpdater.SetFPS(fps);
}

int CDrawableGameObject::DrawFPS() const
{
    return m_DrawUpdater.FPS();
}

void CDrawableGameObject::ProcessUpdate(const CGameTime& gameTime)
{
    OnDraw(gameTime);
}


} // namespace csmeg
