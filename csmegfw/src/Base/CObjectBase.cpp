#include "CObjectBase.h"

namespace csmeg {

CObjectBase::CObjectBase() : m_IsInitialized(false), m_LastError(CSMResultAllOk)
{
}

CObjectBase::~CObjectBase()
{
}

bool CObjectBase::initialize()
{
    m_IsInitialized = onInitialize();
    return m_IsInitialized;
}

void CObjectBase::release()
{
    onRelease();
}

} // namespace csmeg

