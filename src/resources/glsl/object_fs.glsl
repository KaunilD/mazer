#version 440

in vec4 vs_position;

out vec4 fs_color;

void main()
{
	fs_color = vs_position;
}