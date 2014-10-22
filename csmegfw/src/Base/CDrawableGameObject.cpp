#include "CDrawableGameObject.h"

using namespace csmeg;

CDrawableGameObject::CDrawableGameObject() : m_DrawUpdater(0)
{
}

CDrawableGameObject::~CDrawableGameObject()
{
}

void CDrawableGameObject::draw(const CGameTime& gameTime) const
{
    CDrawableGameObject* obj = const_cast<CDrawableGameObject*>(this);
    if( obj->m_DrawUpdater.tick(gameTime)) {
        onDraw(gameTime);
    }
}

void CDrawableGameObject::setRenderInterval(int intervalMsec)
{
    m_DrawUpdater.setUpdateInterval(intervalMsec);
}

int CDrawableGameObject::getRenderInterval() const
{
    return m_DrawUpdater.getUpdateInterval();
}

void CDrawableGameObject::onLoadContent()
{
}

void CDrawableGameObject::onUnloadContent()
{
}

void CDrawableGameObject::onUpdate(const CGameTime& /* gameTime */)
{
}

