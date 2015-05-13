#include "TRectangle.h"

using namespace csmeg;
#include <glm/vec4.hpp>
TRectangle::TRectangle() : TRectangle(0.0f, 0.0f, 0.0f, 0.0f)
{
}

TRectangle::TRectangle(const TRectangle& other) : m_pos(other.m_pos), m_size(other.m_size)
{
}

TRectangle::TRectangle(float x, float y, float w, float h)
    : m_pos(glm::vec2(x, y)), m_size(glm::vec2(w, h))
{
}

TRectangle::TRectangle(const glm::vec2& position, const glm::vec2& size)
    : m_pos(position), m_size(size)
{
}
