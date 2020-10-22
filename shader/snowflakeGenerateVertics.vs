#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 verticeOffset;
layout (location = 2) in vec3 offset;
layout (location = 3) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 u;
uniform vec3 v;
uniform float sizeScale;

out vec2 TexCoord;


void main()
{
    vec3 tempPostion = position + offset + sizeScale * verticeOffset.x * u + sizeScale * verticeOffset.y * v;
    gl_Position = projection * view * model * vec4(tempPostion, 1.0);
    TexCoord = aTexCoord;
}