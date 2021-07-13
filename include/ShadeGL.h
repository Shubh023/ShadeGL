//
// Created by shubh on 7/13/21.
//

#ifndef SHADEGL_SHADEGL_H
#define SHADEGL_SHADEGL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <map>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>

struct key {
    bool cur, prev;
};



static void glClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static void glCheckError()
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}



#endif //SHADEGL_SHADEGL_H
