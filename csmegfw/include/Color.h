#ifndef CSMEGFW_COLOR_H
#define CSMEGFW_COLOR_H

#include <stdint.h>

namespace csmeg {

	class Color
	{
	public: 
		enum class Palette
		{
			Black,
			Red,
			Green,
			Blue
		};

	public:
		Color();
//		Color(Palette color);
		Color(float r, float g, float b);
		Color(float r, float g, float b, float a);
		virtual ~Color();

	public: // Data
		float red;
		float green;
		float blue;
		float alpha;
	};
}

#endif // CSMEGFW_COLOR_H

