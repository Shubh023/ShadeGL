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

#define GRAVITY -50
void glClearError();
void glCheckError(const char* s);
void input();

#endif //SHADEGL_SHADEGL_H
