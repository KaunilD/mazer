#version 330 core

uniform sampler2D texture1;

in vec4 vs_position;
in vec3 vs_color;
in vec3 vs_normal;
in vec2 vs_texture;

out vec4 gl_FragColor;


void main()
{
	gl_FragColor = texture(texture1, vs_texture);
}