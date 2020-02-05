#version 440

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec3 vertex_normal;

uniform highp mat4 modelMatrix;
uniform highp mat4 viewMatrix;
uniform highp mat4 projectionMatrix;

uniform highp vec3 u_vs_color;

out vec4 vs_position;
out vec3 vs_color;
out vec3 vs_normal;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_position, 1.f);
	
	vs_position = gl_Position;
	vs_color = u_vs_color;
	vs_normal = vertex_normal;
}