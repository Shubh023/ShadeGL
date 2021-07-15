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
    explicit EBO(std::vector<GLuint>& indices);

    void bind();
    void unbind();
    void del();

    GLuint ID;
};

#endif //SHADEGL_EBO_H
