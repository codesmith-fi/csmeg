#include "CDrawableGameObject.h"

using namespace csmeg;

CDrawableGameObject::CDrawableGameObject()
{
}

CDrawableGameObject::~CDrawableGameObject()
{
}

void CDrawableGameObject::draw() const
{
    onDraw();
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

