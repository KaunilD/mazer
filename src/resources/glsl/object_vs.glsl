#version 440

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec3 vertex_normal;

out vec4 vs_position;


void main()
{
	gl_Position = vec4(vertex_position, 1.f);
	
	// multiply vertex_position with model and view matrix to give an effect 
	// of a stationary light source illuminating different parts of the object
	// as it changes views.

	vs_position = gl_Position;
	
}