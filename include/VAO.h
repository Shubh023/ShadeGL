//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_VAO_H
#define SHADEGL_VAO_H


#include <ShadeGL.h>
#include <Shader.h>
#include <VBO.h>

class VAO {
public:
    // ID reference for the Vertex Array Object
    GLuint ID;
    // Constructor that generates a VAO ID
    VAO();

    // Links a VBO to the VAO using a certain layout
    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    // Binds the VAO
    void Bind();
    // Unbinds the VAO
    void Unbind();
    // Deletes the VAO
    void Delete();
};


#endif //SHADEGL_VAO_H
