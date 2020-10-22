#version 330 core
layout (location = 0) in vec3 position;

uniform vec3 offsets[100];


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    vec3 offset = offsets[gl_InstanceID];

/*
    mat4 newmodel = model;
    newmodel[0][3] = offset[0];
    newmodel[1][3] = offset[1];
    newmodel[2][3] = offset[2];

    mat4 viewmodel = view * newmodel;
*/
/*
    for (int row = 0; row < 3; row ++) {
        for (int col = 0; col < 3; col++) {
            viewmodel[row][col] = (row == col) ? 1 : 0;
        }
    }

*/
    //gl_Position = projection * viewmodel * vec4(position, 1.0);
    gl_Position = projection * view * model * vec4(position + offset, 1.0);

}