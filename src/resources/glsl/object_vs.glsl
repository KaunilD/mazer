#version 440

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec3 vertex_normal;

uniform highp mat4 modelMatrix;
uniform highp mat4 viewMatrix;
uniform highp mat4 projectionMatrix;


out vec4 vs_position;


void main()
{
	gl_Position =  viewMatrix * modelMatrix * vec4(vertex_position, 1.f);
	vs_position = gl_Position;
	
}