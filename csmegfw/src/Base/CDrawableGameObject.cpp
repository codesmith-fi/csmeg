#include "CDrawableGameObject.h"
#include <boost/bind.hpp>

namespace csmeg
{

CDrawableGameObject::CDrawableGameObject()
{
    m_DrawUpdaterConnection = m_DrawUpdater.connect(boost::bind(&CDrawableGameObject::ProcessUpdate, this, _1));
}

CDrawableGameObject::~CDrawableGameObject()
{
    m_DrawUpdaterConnection.disconnect();
}

void CDrawableGameObject::Draw(const CGameTime& gameTime) const
{
    // TODO optimization, always uses signals to trigger OnDraw.
    // This could call directly OnDraw() if FPS is set to unlimited (0)
    CDrawableGameObject* obj = const_cast<CDrawableGameObject*>(this);
    obj->m_DrawUpdater.Update(gameTime);
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
