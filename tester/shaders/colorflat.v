#version 330

layout(location = 0) in vec3 vertexPosition_model;

void main(){

    gl_Position.xyz = vertexPosition_model;
    gl_Position.w = 1.0;
}
