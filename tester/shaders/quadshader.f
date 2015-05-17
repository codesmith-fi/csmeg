#version 330 core

in vec2 UV;
out vec4 color;

uniform vec4 quadColor;
uniform sampler2D image;
uniform bool enableTexture;

void main()
{
	if(enableTexture) {
		color = quadColor * texture(image, UV);
	} else {
		color = quadColor;
	}
}
