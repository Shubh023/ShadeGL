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
    VAO();

    static void link(VBO& VBO, GLuint format, GLuint np, GLenum type, GLsizeiptr sd, void* off);
    void bind();
    void unbind();
    void del();

    GLuint ID{};
};


#endif //SHADEGL_VAO_H
