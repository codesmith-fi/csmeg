#ifndef CSMEGFW_COLOR_H
#define CSMEGFW_COLOR_H

#include <glm/gtc/type_ptr.hpp>
#include <stdint.h>

namespace csmeg {
  
	class Color
	{
	public: 
        enum ColorComponents : int
        {
            ComponentRed = 0,
            ComponentGreen,
            ComponentBlue,
            ComponentAlpha,
            ComponentCount
        };

	public:
		Color();
        virtual ~Color();

		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);

        float red() const { return m_parts[ComponentRed]; }
        float green() const { return m_parts[ComponentGreen]; }
        float blue() const { return m_parts[ComponentBlue]; }
        float alpha() const { return m_parts[ComponentAlpha]; }

	public: // Data
        // r,g,b,a 
        float m_parts[ComponentCount];
	};
    
}

#endif // CSMEGFW_COLOR_H

