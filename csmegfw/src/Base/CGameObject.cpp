#include "CGameObject.h"
#include <CGameTime.h>

using namespace csmeg;

CGameObject::CGameObject()
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::update(const CGameTime& gameTime)
{
    onUpdate(gameTime);
}

void CGameObject::loadContent()
{
    return onLoadContent();
}

void CGameObject::unloadContent()
{
    return onUnloadContent();
}
