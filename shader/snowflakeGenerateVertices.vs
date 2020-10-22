#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 verticeOffset;


uniform vec3 offsets[100];
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 u;
uniform vec3 v;

void main()
{
    vec3 offset = offsets[gl_InstanceID];
    vec3 tempPostion = position + offset + verticeOffset.x * u + verticeOffset.y * v;

    gl_Position = projection * view * model * vec4(tempPostion, 1.0);
}