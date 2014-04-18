#include "CObjectBase.h"

namespace csmeg {

CObjectBase::CObjectBase() : m_LastError(CSMResultAllOk)
{
}

CObjectBase::~CObjectBase()
{
}

bool CObjectBase::Initialize()
{
    m_IsInitialized = OnInitialize();
    return m_IsInitialized;
}

void CObjectBase::Release()
{
    OnRelease();
}

} // namespace csmeg

