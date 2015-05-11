#ifndef __TRectangle_H_DEFINED__
#define __TRectangle_H_DEFINED__

#include <TVector2.h>

namespace csmeg
{
    class TRectangle
    {
    public:
        TRectangle();
        TRectangle(const TRectangle& other);
        TRectangle(float x, float y, float w, float h);
        TRectangle(const TVector2& position, const TVector2& size);
        ~TRectangle();

        // Operators
        TRectangle& operator=(const TRectangle& other);

        // Getters
        float x() const { return m_Position.x(); }
        float y() const { return m_Position.y(); };
        float w() const { return m_Size.x(); };
        float h() const { return m_Size.y(); };
        TVector2 position() const { return m_Position; }
        TVector2 size() const { return m_Size; }
        TVector2 bottomRight() const;
        TVector2 topLeft() const { return m_Position; }
        bool isWithin(const TRectangle& boundaries) const;

        // Modifiers
        void move(const TVector2& diff);
        void shrink(float amount);
        void enlarge(float amount);
        void setPosition(const TVector2& position);
        void setSize(const TVector2& size);
        void setSize(float w, float h);

    private: // data
        TVector2 m_Position;
        TVector2 m_Size;
    };
}

#endif // __TRectangle_H_DEFINED__
