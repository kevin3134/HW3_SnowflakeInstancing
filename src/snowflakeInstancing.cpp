/* *
 * Windows in cmd
 * cd build 
 * cmake -G "Unix Makefiles" ../    (to avoid using VS gcc generater in windows)
 * make
 * .\snowflakeInstancing.exe
 * 
 * */
#include <iostream>
#include <algorithm>
#include <time.h>

// GLM Math Library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>


// GLAD: A library that wraps OpenGL functions to make things easier
//       Note that GLAD MUST be included before GLFW
#include "glad/glad.h"
// GLFW: A library that helps us manage windows
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Camera.h"
#include "Skybox.h"

// **********GLFW window related functions**********
// Returns pointer to a initialized window with OpenGL context set up
GLFWwindow *init();
// Sometimes user might resize the window. so the OpenGL viewport should be adjusted as well.
void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
// User input is handled in this function
void processInput(GLFWwindow *window);
// Mouse input is handled in this function
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void scrollCallback(GLFWwindow *window, double offsetX, double offsetY);

// **********GLFW window related attributes**********
int gScreenWidth = 800;
int gScreenHeight = 600;
float gDeltaTime = 0.0f;
float gLastFrame = 0.0f;
GLfloat pi_half = 3.1415 / 2;

Camera gCamera;

int main()
{
    GLFWwindow *window = init();
    if (window == nullptr) {
        std::cout << "Failed to initialize GLFW and OpenGL!" << std::endl;
        return -1;
    }
    // add skybox and its shader
    std::vector<std::string> skyboxPaths = {
            "../texture/Sunset/SunsetLeft2048.png",
            "../texture/Sunset/SunsetRight2048.png",
            "../texture/Sunset/SunsetUp2048.png",
            "../texture/Sunset/SunsetDown2048.png",
            "../texture/Sunset/SunsetFront2048.png",
            "../texture/Sunset/SunsetBack2048.png",
    };
    Shader skyboxShader("../shader/background.vs", "../shader/background.fs");
    Skybox skybox(skyboxPaths);

    Shader snowShader("../shader/snowflake.vs", "../shader/snowflake.fs");

    GLfloat planeVertices[] = {
        // Positions          // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
        -1.0f, -1.0f,  0.0f,  //2.0f,  0.0f,
        -1.0f, 1.0f,  0.0f,  //0.0f,  0.0f,
        1.0f, -1.0f,  0.0f,  //0.0f,  2.0f,

        -1.0f, 1.0f,  0.0f,  //2.0f,  0.0f,
        1.0f, 1.0f,  0.0f,  //0.0f,  0.0f,
        1.0f, -1.0f,  0.0f,  //2.0f,  2.0f
    };

    // Setup plane VAO
    GLuint planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);


    glEnable(GL_DEPTH_TEST);
    //gamma correction
    glEnable(GL_FRAMEBUFFER_SRGB);
    //anti-aliasing
    glEnable(GL_MULTISAMPLE);
    //consider blend color using the original alpha value (RGBA)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gCamera.Position = glm::vec3(0.0f, 0.0f, 15.0f);
    int thetaSign_row1 = 0;
    int thetaSign_row2 = 0;
    //threshold for the acos result to change sign
    GLfloat changeSignThreshold = 0.2f; 

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Calculate how much time since last frame
        auto currentFrame = (float)glfwGetTime();
        gDeltaTime = currentFrame - gLastFrame;
        gLastFrame = currentFrame;

        // Handle user input
        processInput(window);

        // All the rendering starts from here
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up view and projection matrix
        glm::mat4 view = gCamera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(gCamera.Zoom),
                                                (float)gScreenWidth / gScreenHeight, 0.1f, 100.0f);
        glm::mat4 model = glm::mat4(1.0f);
        

        glDepthMask(GL_FALSE);
        skybox.Draw(skyboxShader,view,projection);
        glDepthMask(GL_TRUE);


        //get 3 dot for the plane 
        glm::vec3 dot1(planeVertices[0],planeVertices[1],planeVertices[2]);
        glm::vec3 dot2(planeVertices[3],planeVertices[4],planeVertices[5]);
        glm::vec3 dot3(planeVertices[6],planeVertices[7],planeVertices[8]);

        //calculate camera facing vector, and 2 vertical vector in the plane 
        glm::vec3 facing = glm::normalize(gCamera.Position - gCamera.Front);
        glm::vec3 row1 = glm::normalize(dot1 - dot2);
        glm::vec3 row2 = glm::normalize(dot3 - dot1);

        //using acos to get the related theta
        GLfloat theta1 = glm::acos(glm::dot(facing,row1));
        GLfloat theta2 = glm::acos(glm::dot(facing,row2));

        //acos function might not provide the correct sign
        if(thetaSign_row1==0){
            model = glm::rotate(model, pi_half - theta1, dot3-dot1);
        }else{
            model = glm::rotate(model, pi_half + theta1, dot3-dot1);
        }
        if(thetaSign_row2==0){
            model = glm::rotate(model, pi_half - theta2, dot2-dot1);
        }else{
            model = glm::rotate(model, pi_half + theta2, dot2-dot1);
        }

        //acos function need to change sign after 2 vectors met
        //we just simply check if the dot product of newrow and facing
        //is too large
        glm::vec3 newrow1(model * glm::vec4(row1, 0.0f));
        GLfloat dotRow1 = glm::dot(newrow1, facing);
        std::cout<<dotRow1<<std::endl;
        if(dotRow1 > changeSignThreshold || dotRow1 < -changeSignThreshold){
            thetaSign_row1 = !thetaSign_row1;
        }

        glm::vec3 newrow2(model * glm::vec4(row2, 0.0f));
        GLfloat dotRow2 = glm::dot(newrow2, facing);
        //std::cout<<dotRow2<<std::endl;
        if(dotRow2 > changeSignThreshold || dotRow2 < -changeSignThreshold){
            thetaSign_row2 = !thetaSign_row2;
        }

        //std::cout<<facing<<std::endl;
        //std::cout<<theta2<<std::endl;

        snowShader.use();
        snowShader.setMat4("view", view);
        snowShader.setMat4("projection", projection);
        snowShader.setMat4("model", model);

        glBindVertexArray(planeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // Rendering Ends here
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);

    glfwTerminate();
    return 0;
}


GLFWwindow *init()
{
    // Initialization of GLFW context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Something needed for Mac OS X
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // For anti-aliasing effects
    glfwWindowHint(GLFW_SAMPLES, 4);


    // Create a window object
    GLFWwindow *window = glfwCreateWindow(gScreenWidth, gScreenHeight, "Window Title", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD before calling OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    // Tell OpenGL the size of rendering window
    glViewport(0, 0, gScreenWidth * 2, gScreenHeight * 2);

    // Set the windows resize callback function
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    // Set up mouse input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    return window;
}

void frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
    gScreenWidth = width;
    gScreenHeight = height;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    // Exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Handle camera movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
    }

    //print camera position
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        gCamera.debug_printPosition();
    }
    //print camera front
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        gCamera.debug_printFront();
    }
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    // Variables needed to handle mouse input
    static float lastMouseX = 400.0f;
    static float lastMouseY = 300.0f;
    static bool firstMouse = true;

    if (firstMouse) {
        lastMouseX = (float)xpos;
        lastMouseY = (float)ypos;
        firstMouse = false;
    }

    // Calculate mouse movement since last frame
    float offsetX = (float)xpos - lastMouseX;
    float offsetY = (float)ypos - lastMouseY;
    lastMouseX = (float)xpos;
    lastMouseY = (float)ypos;

    gCamera.ProcessMouseMovement(offsetX, offsetY);
}

void scrollCallback(GLFWwindow *window, double offsetX, double offsetY)
{
    gCamera.ProcessMouseScroll((float)offsetY);
}