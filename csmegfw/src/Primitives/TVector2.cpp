#include "TVector2.h"
#include "TRectangle.h"

using namespace csmeg;

TVector2::TVector2() : TVector2(0.0f, 0.0f)
{
}


TVector2::~TVector2()
{
}

TVector2::TVector2(const TVector2& other)
{
    *this = other;
}

TVector2::TVector2(float x, float y) : m_X(x), m_Y(y)
{
}

TVector2& TVector2::operator=(const TVector2& other)
{
    m_X = other.m_X;
    m_Y = other.m_Y;
    return *this;
}

bool TVector2::operator==(const TVector2& other)
{
    return((m_X == other.m_X) && (m_Y == other.m_Y));
}

bool TVector2::operator!=(const TVector2& other)
{
    return !(*this == other);
}

bool TVector2::isWithin(const TRectangle& boundaries) const
{
    return((*this >= boundaries.position()) 
        && (*this <= boundaries.bottomRight()));
}

TVector2 TVector2::unit() const
{
    TVector2 res;
    float max(getMaxXY());
    if(max != 0.0f) {
        res.m_X = m_Y * max;
        res.m_Y = m_Y * max;
    }
    return res;
}

void TVector2::normalize()
{
    float max(getMaxXY());
    if(max != 0.0f) {
        m_X /= max;
        m_Y /= max;
    }
    else {
        zero();
    }
}

void TVector2::zero()
{
    m_X = 0.0f;
    m_Y = 0.0f;
}
