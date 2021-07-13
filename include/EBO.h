//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_EBO_H
#define SHADEGL_EBO_H

#include <ShadeGL.h>
#include <Shader.h>

class EBO
{
public:
    // ID reference of Elements Buffer Object
    GLuint ID;
    // Constructor that generates a Elements Buffer Object and links it to indices
    EBO(GLuint* indices, GLsizeiptr size);

    // Binds the EBO
    void Bind();
    // Unbinds the EBO
    void Unbind();
    // Deletes the EBO
    void Delete();
};

#endif //SHADEGL_EBO_H
