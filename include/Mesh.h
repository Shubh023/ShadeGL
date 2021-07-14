//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_MESH_H
#define SHADEGL_MESH_H

#include <string>
#include <vector>
#include <VAO.h>
#include <VBO.h>
#include <EBO.h>
#include <Camera.h>
#include <Texture.h>


class Mesh {
public:

    Mesh(std::vector<Vertex>& _vertices, std::vector<GLuint>& _indices, std::vector<Texture>& _textures);
    void Draw(Shader& shader, Camera& camera);

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    VAO vao;
};

#endif //SHADEGL_MESH_H
