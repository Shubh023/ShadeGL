//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_VBO_H
#define SHADEGL_VBO_H

#include <ShadeGL.h>
#include <Shader.h>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

class VBO {
public:
    explicit VBO(std::vector<Vertex>& vertices);

    void bind() const;
    static void unbind();
    void del();

    GLuint id;
};

#endif //SHADEGL_VBO_H
