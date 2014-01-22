#include "CDrawableGameObject.h"

namespace csmeg
{

CDrawableGameObject::CDrawableGameObject()
{
    //ctor
}

CDrawableGameObject::~CDrawableGameObject()
{
    //dtor
}

void CDrawableGameObject::Draw(const CGameTime& gameTime) const
{
    OnDraw(gameTime);
}

} // namespace csmeg
