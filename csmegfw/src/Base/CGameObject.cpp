#include "CGameObject.h"

namespace csmeg
{

CGameObject::CGameObject()
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::Update(const CGameTime& gameTime)
{
    OnUpdate(gameTime);
}

void CGameObject::Initialize()
{
    OnRelease();
}

void CGameObject::Release()
{
    OnRelease();
}

} // namespace csmeg

