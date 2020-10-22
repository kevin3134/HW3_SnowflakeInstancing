#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

struct SnowflakePlane{
    GLfloat planeVertices[42];
    GLfloat sizeScale;
};

void genTranslation(int translationRowCount, glm::vec3 *translations);

void setSnowflakePlane(GLfloat sizeScale, SnowflakePlane * snowflakePlane);

#endif