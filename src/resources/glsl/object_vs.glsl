#version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texture;
layout (location = 3) in vec3 vertex_color;

uniform highp mat4 modelMatrix;
uniform highp mat4 viewMatrix;
uniform highp mat4 projectionMatrix;

uniform highp vec3 u_vs_color;

out vec4 vs_position;
out vec3 vs_normal;
out vec2 vs_texture; 
out vec3 vs_color;

void main(){
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex_position, 1.f);
	
	vs_position = gl_Position;
	vs_normal = vertex_normal;
	vs_texture = vec2(vertex_texture.x, vertex_texture.y);
	vs_color = vec3(1.0, 0, 1.0);
}