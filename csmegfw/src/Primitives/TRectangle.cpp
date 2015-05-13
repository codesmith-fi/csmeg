#include "TRectangle.h"

using namespace csmeg;

TRectangle::TRectangle() : TRectangle(0.0f, 0.0f, 0.0f, 0.0f)
{
}

TRectangle::TRectangle(const TRectangle& other) : m_pos(other.m_pos), m_size(other.m_size)
{
}

TRectangle::TRectangle(float x, float y, float w, float h)
    : m_pos(TVector2(x, y)), m_size(TVector2(w, h))
{
}

TRectangle::TRectangle(const TVector2& position, const TVector2& size)
    : m_pos(position), m_size(size)
{
}
