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

// Helpful functions for debug
void glClearError();
void glCheckError(const char* s);

// Register inputs and update variables accordingly
void input();

#endif //SHADEGL_SHADEGL_H
