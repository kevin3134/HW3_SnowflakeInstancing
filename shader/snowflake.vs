#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 offsetsMat[100];
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    mat4 offsetMat = offsetsMat[gl_InstanceID];
    mat4 viewmodel = view * offsetMat * model;

    for (int row = 0; row < 3; row ++) {
        for (int col = 0; col < 3; col++) {
            viewmodel[row][col] = (row == col) ? 1 : 0;
        }
    }

    gl_Position = projection * viewmodel * vec4(position, 1.0);
}