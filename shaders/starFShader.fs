#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture_1;

void main()
{
   FragColor = texture(texture_1, TexCoord); // * vec4(ourColor, 1.0);
}