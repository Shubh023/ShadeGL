//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_FLOOR_H
#define SHADEGL_FLOOR_H

#include <VBO.h>

// Vertices coordinates
Vertex floor_v[] =
{
        Vertex{glm::vec3(-10.0f, 0.0f,  10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec2(0.0f, 10.0f)},
        Vertex{glm::vec3( 10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec2(10.0f, 10.0f)},
        Vertex{glm::vec3( 10.0f, 0.0f,  10.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec2(10.0f, 0.0f)}
};

GLuint floor_i[] =
{
    0, 1, 2,
    0, 2, 3
};

#endif //SHADEGL_FLOOR_H
