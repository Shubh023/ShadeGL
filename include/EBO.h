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

    GLuint ID;
    void Bind();
    void Unbind();
    void Delete();
};

#endif //SHADEGL_EBO_H
