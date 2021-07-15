//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_SKYBOX_H
#define SHADEGL_SKYBOX_H

#include <Mesh.h>

float skybox_vertices[] =
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

unsigned int skybox_indices[] =
{
    1, 2, 6,
    6, 5, 1,
    0, 4, 7,
    7, 3, 0,
    4, 5, 6,
    6, 7, 4,
    0, 3, 2,
    2, 1, 0,
    0, 1, 5,
    5, 4, 0,
    3, 7, 6,
    6, 2, 3
};

// TODO : Get some images from https://hdrihaven.com/ and try out what works the best for pogl scene
// Used https://matheowis.github.io/HDRI-to-CubeMap/ to get images of 6 faces
// px should be flipped vertically and sometimes horizontally as well
std::string dayCubemap[6] =
{
    "../resources/skybox/day/px.png",
    "../resources/skybox/day/nx.png",
    "../resources/skybox/day/py.png",
    "../resources/skybox/day/ny.png",
    "../resources/skybox/day/pz.png",
    "../resources/skybox/day/nz.png",
};

std::string nightCubemap[6] =
{
    "../resources/skybox/night/px.png",
    "../resources/skybox/night/nx.png",
    "../resources/skybox/night/py.png",
    "../resources/skybox/night/ny.png",
    "../resources/skybox/night/pz.png",
    "../resources/skybox/night/nz.png",
};


#endif //SHADEGL_SKYBOX_H
