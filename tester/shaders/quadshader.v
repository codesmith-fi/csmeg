#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 tex;
out vec2 UV;

// mvp = projection * view * model
uniform mat4 mvp;

void main()
{
	UV = tex;
	gl_Position = mvp * vec4(vertex.xyz, 1.0);	
}
