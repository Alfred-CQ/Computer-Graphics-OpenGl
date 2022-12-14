#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture_1;
uniform sampler2D texture_2;

void main()
{
   FragColor = mix(texture(texture_1, TexCoord), texture(texture_2, TexCoord), 0.2);
}