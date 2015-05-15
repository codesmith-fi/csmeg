#include "Color.h"

using namespace csmeg;

namespace
{   
    const glm::vec4 gPalette[] = {
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), // black
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), // red
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), // green
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), // blue
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), // white
    };
}

Color::Color(Palette color)
{
    m_color = gPalette[static_cast<int>(color)];
}

Color& Color::operator=(const Color& other)
{ 
    m_color = other.m_color;
    return *this;
}
