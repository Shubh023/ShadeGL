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
    // Reference ID of the Vertex Buffer Object
    GLuint ID;
    // Constructor that generates a Vertex Buffer Object and links it to vertices
    explicit VBO(std::vector<Vertex>& vertices);

    // Binds the VBO
    void Bind() const;
    // Unbinds the VBO
    static void Unbind();
    // Deletes the VBO
    void Delete();
};

#endif //SHADEGL_VBO_H
