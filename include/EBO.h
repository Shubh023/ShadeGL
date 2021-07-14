//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_EBO_H
#define SHADEGL_EBO_H

#include <ShadeGL.h>
#include <Shader.h>
#include <vector>

class EBO
{
public:
    // ID reference of Elements Buffer Object
    GLuint ID;
    // Constructor that generates a Elements Buffer Object and links it to indices
    explicit EBO(std::vector<GLuint>& indices);

    // Binds the EBO
    void Bind();
    // Unbinds the EBO
    void Unbind();
    // Deletes the EBO
    void Delete();
};

#endif //SHADEGL_EBO_H
