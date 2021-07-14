//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_BOX_H
#define SHADEGL_BOX_H

#include <Mesh.h>

#define cx 0.1f
#define cy 0.1f
#define cz 0.1f

Vertex box_vertices[] = {
    Vertex{glm::vec3(-cx, -cy,  cz)},
    Vertex{glm::vec3(-cx, -cy, -cz)},
    Vertex{glm::vec3( cx, -cy, -cz)},
    Vertex{glm::vec3( cx, -cy,  cz)},
    Vertex{glm::vec3(-cx,  cy,  cz)},
    Vertex{glm::vec3(-cx,  cy, -cz)},
    Vertex{glm::vec3( cx,  cy, -cz)},
    Vertex{glm::vec3( cx,  cy,  cz)}
};

GLuint box_indices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

#endif //SHADEGL_BOX_H
