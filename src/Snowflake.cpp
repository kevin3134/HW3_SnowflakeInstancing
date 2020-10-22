#include "Snowflake.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

static inline float randf(float min, float max, int precision = 1000)
{
    if (min > max) std::swap(min, max);
    float delta = max - min;
    auto i = int(delta * precision);
    return ((float)(rand() % i) / (float)precision) + min;
}

static inline int randi(int min, int max)
{
    if (min > max) std::swap(min, max);
    return (rand() % (max - min)) + min;
}

void genTranslation(int translationRowCount, glm::vec3 *translations){

    int index = 0;
    for(GLint z = -translationRowCount; z < translationRowCount; z += 2)
    {
        for(GLint x = -translationRowCount; x < translationRowCount; x += 2)
        {
            for(GLint y = -translationRowCount; y < translationRowCount; y += 2){
                glm::vec3 translation;
                translation.x = (GLfloat)x * 3.0f  + randf(-1.0f,1.0f);
                translation.y = (GLfloat)y * 3.0f +  randf(-1.0f,1.0f);
                translation.z = (GLfloat)z * 3.0f +  randf(-1.0f,1.0f);
                translations[index] = translation;
                index++;
            }

        }
    }
}

void setSnowflakePlane(GLfloat inputSizeScale, SnowflakePlane * snowflakePlane){
    GLfloat initplaneVertices[] = {
        // Positions          // vertices position offsets
        0.0f,  0.0f,  0.0f,   -1.0f,  -1.0f,   0.0f, 0.0f, // bottom left
        0.0f,  0.0f,  0.0f,   -1.0f,   1.0f,   0.0f, 1.0f,  // top left 
        0.0f,  0.0f,  0.0f,    1.0f,  -1.0f,   1.0f, 0.0f, // bottom right

        0.0f,  0.0f,  0.0f,    1.0f,  -1.0f,   1.0f, 0.0f, // bottom right
        0.0f,  0.0f,  0.0f,    1.0f,   1.0f,   1.0f, 1.0f, // top right 
        0.0f,  0.0f,  0.0f,   -1.0f,   1.0f,   0.0f, 1.0f  // top left 
    };

    for(int i = 0; i < 42; i++){
        snowflakePlane->planeVertices[i] = initplaneVertices[i];
    }

    snowflakePlane->sizeScale = inputSizeScale;
}


void updateTranslation(int translationRowCount, GLfloat move, glm::vec3 *translations, glm::vec3 *translationsSpeed){
    GLfloat stepX = randf(-1.0f, 1.0f);
    GLfloat stepY = randf(-1.0f, 1.0f);

    GLint SnowflakeCount = translationRowCount * translationRowCount * translationRowCount;
    for(int i = 0; i < SnowflakeCount; i++){

        GLfloat stepX = randf(-1.0f, 1.0f);
        GLfloat stepY = randf(-1.0f, 1.0f);

        translationsSpeed[i].x += stepX;
        translationsSpeed[i].y += stepY;

        if(translations[i].x > 80.0f){
            translationsSpeed[i].x -= 2.0f;
        }else if(translations[i].x < -80.0f){
            translationsSpeed[i].x += 2.0f;
        }

        if(translations[i].y > 80.0f){
            translationsSpeed[i].y -= 2.0f;
        }else if(translations[i].y < -80.0f){
            translationsSpeed[i].y += 2.0f;
        }


        translations[i].x += translationsSpeed[i].x * move;
        translations[i].y += translationsSpeed[i].y * move;
    }
}


void genTranslationSpeed(int translationRowCount, int initSpeedBound, glm::vec3 *translationsSpeed){

    int index = 0;
    for(GLint z = -translationRowCount; z < translationRowCount; z += 2)
    {
        for(GLint x = -translationRowCount; x < translationRowCount; x += 2)
        {
            for(GLint y = -translationRowCount; y < translationRowCount; y += 2){
                glm::vec3 translation;
                translation.x = randf(-initSpeedBound,initSpeedBound);
                translation.y = randf(-initSpeedBound,initSpeedBound);;
                translation.z = 0.0f;
                translationsSpeed[index] = translation;
                index++;
            }

        }
    }
}





