###########################
# Snowflake project CMakeList
# include GLAD, GLFW, GLM
###########################

cmake_minimum_required(VERSION 3.0)
project(InstancingTestChangeView)
project(InstancingTestGenerateVertices)


aux_source_directory(. DIR_TOOT_SRCS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# add_executable(${PROJECT_NAME} ${DIR_TOOT_SRCS})
include_directories(${PROJECT_SOURCE_DIR}/include)

###########################
# GLAD
###########################
# include_directories("glad")
add_executable(InstancingTestChangeView
    src/InstancingTestChangeView.cpp 
    src/glad.c
    src/Skybox.h
    src/Skybox.cpp
    include/Shader.h
    include/Camera.h
)

add_executable(InstancingTestGenerateVertices
    src/InstancingTestGenerateVertices.cpp 
    src/glad.c
    src/Skybox.h
    src/Skybox.cpp
    src/Snowflake.h
    src/Snowflake.cpp
    include/Shader.h
    include/Camera.h
    include/Texture.h
)

###########################
# GLFW
###########################
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(WIN32)
    message(STATUS "starting configure glfw win32")
    add_subdirectory(glfw)
    include_directories(glfw/include)
    target_link_libraries(InstancingTestChangeView glfw ${GLFW_LIBRARIES})
    target_link_libraries(InstancingTestGenerateVertices glfw ${GLFW_LIBRARIES})
endif()

###########################
# GLM
###########################
if(WIN32)
    message(STATUS "starting configure glm win32")
    add_subdirectory(glm)
    include_directories(glm/include)
    target_link_libraries(InstancingTestChangeView glm ${GLM_LIBRARIES})
    target_link_libraries(InstancingTestGenerateVertices glm ${GLM_LIBRARIES})
endif()

##########################
# OPENGL
##########################
find_package(OpenGL REQUIRED)
