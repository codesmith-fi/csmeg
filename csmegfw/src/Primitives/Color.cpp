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

Color::Color(float r, float g, float b, float a) 
{
    m_parts[ComponentRed] = r;
    m_parts[ComponentGreen] = g;
    m_parts[ComponentBlue] = b;
    m_parts[ComponentAlpha] = a;
}

Color::~Color()
{
}
