#ifndef __TRectangle_H_DEFINED__
#define __TRectangle_H_DEFINED__

#include <glm/vec2.hpp>
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
        ~TRectangle() {};

        // Operators

        // Getters
        TVector2 position() const { return m_pos; }
        TVector2 size() const { return m_size; }
        void grow(const TVector2& size) { m_size += size; }
        void shrink(const TVector2& size) { m_size -= size; }
        void move(const TVector2& delta) { m_pos += delta; }
        void setPos(const TVector2& newPos) { m_pos = newPos; }
        void setSize(const TVector2& newSize) { m_size = newSize; }

        TVector2 tl() const { return m_pos; }
        TVector2 br() const { return m_pos + m_size; }
        TVector2 tr() const { return TVector2(m_pos.x + m_size.x, m_pos.y); }
        TVector2 bl() const { return TVector2(m_pos.x, m_pos.y + m_size.y); }
    private: // data
        TVector2 m_pos;
        TVector2 m_size;
    };
}

#endif // __TRectangle_H_DEFINED__
