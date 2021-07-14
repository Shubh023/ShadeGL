//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_SKYBOX_H
#define SHADEGL_SKYBOX_H

#include <Mesh.h>

float skyboxVertices[] =
{
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
        // Right
        1, 2, 6,
        6, 5, 1,

        // Left
        0, 4, 7,
        7, 3, 0,

        // Top
        4, 5, 6,
        6, 7, 4,

        // Bottom
        0, 3, 2,
        2, 1, 0,

        // Back
        0, 1, 5,
        5, 4, 0,

        // Front
        3, 7, 6,
        6, 2, 3
};

// TODO : Get some images from https://hdrihaven.com/ and try out what works the best for pogl scene
// Used https://matheowis.github.io/HDRI-to-CubeMap/ to get images of 6 faces
// px should be flipped vertically and sometimes horizontally as well
std::string facesCubemap[6] =
{
    "../resources/skybox/px.png",
    "../resources/skybox/nx.png",
    "../resources/skybox/py.png",
    "../resources/skybox/ny.png",
    "../resources/skybox/pz.png",
    "../resources/skybox/nz.png",
};

#endif //SHADEGL_SKYBOX_H
