#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

/**
 * SnowflakePlane represent some basical attributes for a single
 * billboard (instance)
 * 
 * planeVertics contains vertices Postions, offset and texture
 * sizeScale change the size of a snowflake plane
 */
struct SnowflakePlane{
    GLfloat planeVertices[42];
    GLfloat sizeScale;
};

//generate translation metrics for billboard to instancing
void genTranslation(int translationRowCount, glm::vec3 *translations);

//init the snowflake plane
void setSnowflakePlane(GLfloat sizeScale, SnowflakePlane * snowflakePlane);

//update Translation (used only if we want to move instances)
void updateTranslation(int translationRowCount, GLfloat move, glm::vec3 *translations, glm::vec3 *translationsSpeed);

//generate translation speed matrics to change translation metric (used only if we want to move instances)
void genTranslationSpeed(int translationRowCount, int initSpeedBound, glm::vec3 *translationsSpeed);
#endif