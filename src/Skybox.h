#ifndef PROJECT_SKYBOX_H
#define PROJECT_SKYBOX_H

#include <iostream>
#include <vector>
#include <string>

// GLM Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"

#include "Shader.h"

class Skybox
{
public:
    Skybox(std::vector<std::string> paths);

    void Draw(Shader &shader, glm::mat4 view, glm::mat4 projection);
public:
    unsigned int texture;
private:
    unsigned int VAO, VBO;

    unsigned int GenCubeMap(std::vector<std::string> facePaths);
};



#endif