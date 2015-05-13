#version 330 core

in vec2 UV;
out vec4 color;

uniform vec4 quadColor;
uniform sampler2D image;

void main()
{
	color = quadColor * texture(image, UV);
}
