#include "Color.h"

using namespace csmeg;

Color::Color() 
	: Color(0.0f, 0.0f, 0.0f, 1.0f)
{

}

Color::Color(float r, float g, float b) 
	: Color(r, g, b, 1.0f)
{

}

Color::Color(float r, float g, float b, float a) : red(r), green(g), blue(b), alpha(a)
{
}

Color::~Color()
{
}

