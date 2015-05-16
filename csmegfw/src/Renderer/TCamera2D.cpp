#include "TCamera2D.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace csmeg;
using renderer::TCamera2D;

TCamera2D::TCamera2D()
    : TCamera2D(TVector2(0.0f, 0.0f))
{
}

TCamera2D::TCamera2D(const TVector2& position) 
    : TCamera2D(position, TVector2(0.0f, 0.0f), 0.0f, 0.0f)
{
}

TCamera2D::TCamera2D(const TVector2& position, const TVector2& origin)
    : TCamera2D(position, origin, 0.0f, 0.0f)
{
}

TCamera2D::TCamera2D(const TVector2& position, const TVector2& origin, float rotation, float scale)
    : m_position(position), m_rotation(rotation), m_scale(scale)
{
    update();
}


TCamera2D::~TCamera2D()
{
}

glm::mat4 TCamera2D::get() const
{
    return m_camMatrix;
}

void TCamera2D::rotate(float angle)
{
    m_rotation += angle;
    update();
}

void TCamera2D::move(const TVector2& delta)
{
    m_position += delta;
    update();
}

void TCamera2D::scale(float delta)
{
    m_scale += delta;
    update();
}

void TCamera2D::setScale(float newScale)
{
    m_scale = newScale;
    update();
}

void TCamera2D::setPosition(const TVector2& newPosition)
{
    m_position = newPosition;
    update();
}

void TCamera2D::setOrigin(const TVector2& newOrigin)
{
    m_origin = newOrigin;
    update();
}

void TCamera2D::setRotation(float newRotation)
{
    m_rotation = newRotation;
    update();
}

void TCamera2D::update()
{
    glm::mat4 m;
    m = glm::translate(m, glm::vec3(-m_position, 0.0f));
    m = glm::scale(m, glm::vec3(m_scale, m_scale, 1.0f));
    m = glm::rotate(m, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    m_camMatrix = glm::translate(m, glm::vec3(m_origin, 0.0f));
}
