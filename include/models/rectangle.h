//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_RECTANGLE_H
#define SHADEGL_RECTANGLE_H

// Rectangle for FBO (Frame Buffer)
float rectangle_vertices[] = {
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

#endif //SHADEGL_RECTANGLE_H
