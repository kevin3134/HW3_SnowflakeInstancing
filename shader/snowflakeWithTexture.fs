#version 330 core
in vec2 TexCoord;
out vec4 color;

// texture sampler
uniform sampler2D texture1;

void main()
{
    color = texture(texture1, TexCoord);
}