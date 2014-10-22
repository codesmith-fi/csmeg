#include "CGameObject.h"
#include <CGameTime.h>

using namespace csmeg;

CGameObject::CGameObject() : m_Updater(0)
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::update(const CGameTime& gameTime)
{
    if(m_Updater.tick(gameTime)) {
        onUpdate(gameTime);
    }
}

void CGameObject::loadContent()
{
    return onLoadContent();
}

void CGameObject::unloadContent()
{
    return onUnloadContent();
}

void CGameObject::setUpdateInterval(int intervalMsec)
{
    m_Updater.setUpdateInterval(intervalMsec);
}

int CGameObject::getUpdateInterval() const
{
    return m_Updater.getUpdateInterval();
}

