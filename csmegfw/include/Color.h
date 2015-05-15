#ifndef CSMEGFW_COLOR_H
#define CSMEGFW_COLOR_H

#include <glm/gtc/type_ptr.hpp>
#include <stdint.h>

namespace csmeg {
  
	class Color
	{
	public: 
        enum class Palette
        {
            Black = 0,
            Red,
            Green,
            Blue,
            White,
            ColorCount
        };

	public:
        Color() : m_color(0.0f, 0.0f, 0.0f, 1.0f) { ; }
        Color(Palette color);
        Color(float r, float g, float b) : m_color(r, g, b, 1.0f) { ; }
        Color(float r, float g, float b, float a) : m_color(r, g, b, a) { ; }
        Color(const Color& other) { m_color = other.m_color; }
        virtual ~Color() { ; }
    public: // operators
        Color& operator=(const Color& other);
        operator glm::vec4() { return m_color; }

    public: // getters
        glm::vec4 asVec4() const { return m_color; }

        float red() const { return m_color.r; }
        float green() const { return m_color.g; }
        float blue() const { return m_color.b; }
        float alpha() const { return m_color.a; }

	private: // Data
        // r,g,b,a 
        glm::vec4 m_color;
	};
    
}

#endif // CSMEGFW_COLOR_H

