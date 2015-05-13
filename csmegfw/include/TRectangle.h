#ifndef __TRectangle_H_DEFINED__
#define __TRectangle_H_DEFINED__

#include <glm/vec2.hpp>

namespace csmeg
{
    class TRectangle
    {
    public:
        TRectangle();
        TRectangle(const TRectangle& other);
        TRectangle(float x, float y, float w, float h);
        TRectangle(const glm::vec2& position, const glm::vec2& size);
        ~TRectangle() {};

        // Operators

        // Getters
        glm::vec2 position() const { return m_pos; }
        glm::vec2 size() const { return m_size; }
        void grow(const glm::vec2& size) { m_size += size; }
        void shrink(const glm::vec2& size) { m_size -= size; }
        void move(const glm::vec2& delta) { m_pos += delta; }
        void setPos(const glm::vec2& newPos) { m_pos = newPos; }
        void setSize(const glm::vec2& newSize) { m_size = newSize; }

        glm::vec2 tl() const { return m_pos; }
        glm::vec2 br() const { return m_pos + m_size; }
        glm::vec2 tr() const { return glm::vec2(m_pos.x + m_size.x, m_pos.y); }
        glm::vec2 bl() const { return glm::vec2(m_pos.x, m_pos.y + m_size.y); }
    private: // data
        glm::vec2 m_pos;
        glm::vec2 m_size;
    };
}

#endif // __TRectangle_H_DEFINED__
