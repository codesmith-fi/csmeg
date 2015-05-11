#include "TRectangle.h"

using namespace csmeg;

TRectangle::TRectangle() 
    : TRectangle(0.0f, 0.0f, 0.0f, 0.0f)
{
}

TRectangle::TRectangle(const TRectangle& other) 
{
    *this = other;
}

TRectangle::TRectangle(const TVector2& position, const TVector2& size)
{
    m_Position = position;
    m_Size = size;
}

TRectangle::TRectangle(float x, float y, float w, float h)
    : m_Position(x, y), m_Size(w, h)
{    
}

TRectangle::~TRectangle()
{
}

// Operators

TRectangle& TRectangle::operator=(const TRectangle& other)
{
    m_Position = other.m_Position;
    m_Size = other.m_Size;
    return *this;
}

// Modifiers
void TRectangle::move(const TVector2& diff)
{
    m_Position += diff;
}

void TRectangle::shrink(float amount)
{
    m_Size -= amount;
}

void TRectangle::enlarge(float amount)
{
    m_Size += amount;
}

void TRectangle::setPosition(const TVector2& position)
{
    m_Position = position;
}

void TRectangle::setSize(const TVector2& size)
{
    m_Size = size;
}

void TRectangle::setSize(float w, float h)
{
    m_Size = TVector2(w, h);
}

TVector2 TRectangle::bottomRight() const
{
    return(m_Position + m_Size);
}

bool TRectangle::isWithin(const TRectangle& boundaries) const
{
    return (m_Position >= boundaries.m_Position) && (m_Size <= boundaries.m_Size);
}
