#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 tex;
out vec2 UV;

uniform mat4 projection;
uniform mat4 model;

void main()
{
	UV = tex;
	gl_Position = projection * model * vec4(vertex.xyz, 1.0);
}
