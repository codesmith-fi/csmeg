#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 tex;
out vec2 texCoord;

uniform mat4 projection;
uniform mat4 model;

void main()
{
//	texCoord = tex;
//	gl_Position = projection * model * vec4(vertex.xyz, 1.0);
	gl_Position = projection * model * vec4(vertex.xyz, 1.0);
//	gl_Position.xyz = vertex;
//	gl_Position.w = 1.0;
}
