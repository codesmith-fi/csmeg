#version 330 core

in vec2 UV;
out vec4 color;

uniform vec4 quadColor;

void main()
{
    color = quadColor;
}
