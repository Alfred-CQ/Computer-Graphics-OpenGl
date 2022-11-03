#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture_1;

// default colors
uniform vec4 null_matrix;
uniform vec4 default_colors;

void main()
{
	FragColor = (texture(texture_1, TexCoord) * null_matrix) + default_colors;
}