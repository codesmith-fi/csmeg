#ifndef __VECTOR_H_DEFINED__
#define __VECTOR_H_DEFINED__

namespace csmeg
{
    class TRectangle;

    class TVector2
    {
    public:
        TVector2();
        TVector2(const TVector2& other);
        TVector2(float x, float y);
        ~TVector2();

        // operators
        TVector2& operator=(const TVector2& other);
        
        TVector2& operator+=(const TVector2& other)
        {
            m_X += other.m_X;
            m_Y += other.m_Y;
            return *this;
        }

        TVector2& operator-=(const TVector2& other)
        {
            m_X -= other.m_X;
            m_Y -= other.m_Y;
            return *this;
        }

        TVector2& operator+=(float amount)
        {
            m_X += amount;
            m_Y += amount;
            return *this;
        }

        TVector2& operator-=(float amount)
        {
            m_X -= amount;
            m_Y -= amount;
            return *this;
        }

        TVector2& operator*=(float mult)
        {
            m_X *= mult;
            m_Y *= mult;
        }

        friend TVector2 operator+(const TVector2& lhs, const TVector2& rhs) 
        { 
            TVector2 res(lhs);
            res += rhs;
            return res;
        }

        friend TVector2 operator-(const TVector2& lhs, const TVector2& rhs)
        {
            TVector2 res(lhs);
            res -= rhs;
            return res;
        }

        friend TVector2 operator+(const TVector2& vec, float amount)
        {
            TVector2 res(vec);
            res += amount;
            return res;
        }

        friend TVector2 operator-(const TVector2& vec, float amount)
        {
            TVector2 res(vec);
            res -= amount;
            return res;
        }

        friend TVector2 operator*(const TVector2& vec, float mult)
        {
            TVector2 res(vec);
            res *= mult;
            return res;
        }

        bool operator==(const TVector2& other);
        bool operator!=(const TVector2& other);

        friend bool operator<(const TVector2& lhs, const TVector2& rhs)
        {
            return((lhs.x() < rhs.x()) && (lhs.y() < rhs.y()));
        }

        friend bool operator>(const TVector2& lhs, const TVector2& rhs)
        {
            return rhs < lhs;
        }

        friend bool operator<=(const TVector2& lhs, const TVector2& rhs)
        {
            return !(lhs > rhs);
        }

        friend bool operator>=(const TVector2& lhs, const TVector2& rhs)
        {
            return !(lhs < rhs);
        }

        // getters
        float x() const { return m_X; }
        float y() const { return m_Y; }
        bool isWithin(const TRectangle& boundaries) const;
        float getMaxXY() const { return m_X >= m_Y ? m_X : m_Y; }

        // Modifiers
        void moveX(float amount) { m_X += amount; }
        void moveY(float amount) { m_Y += amount; }
        void normalize();
        TVector2 unit() const;
        void zero();

    private: // data
        float m_X;
        float m_Y;
    };
}

#endif // __VECTOR_H_DEFINED__
