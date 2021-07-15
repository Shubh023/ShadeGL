//
// Created by shubh on 7/14/21.
//

#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices, std::vector<Texture>& _textures) {
    vertices = _vertices;
    indices = _indices;
    textures = _textures;

    vao.bind();
    VBO vbo(vertices);
    EBO ebo(indices);

    vao.link(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.link(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao.link(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    vao.link(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}

void Mesh::render(Shader& shader, Camera& camera)
{
    shader.use();
    vao.bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string num;
        std::string type = textures[i].type;
        if (type == "diffuse")
        {
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        textures[i].assign_unit(shader, (type + num).c_str(), i);
        textures[i].bind();
    }

    // Take care of the camera Matrix
    glUniform3f(glGetUniformLocation(shader.programID, "camPos"), camera.P.x, camera.P.y, camera.P.z);
    camera.matrix(shader, "camMatrix");

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}