//
// Created by shubh on 7/14/21.
//

#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices, std::vector<Texture>& _textures) {
    vertices = _vertices;
    indices = _indices;
    textures = _textures;

    vao.Bind();
    VBO vbo(vertices);
    EBO ebo(indices);

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
    // Bind shader to be able to access uniforms
    shader.use();
    vao.Bind();

    // Keep track of how many of each type of textures we have
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
        textures[i].texUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }
    // Take care of the camera Matrix
    glUniform3f(glGetUniformLocation(shader.programID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
    camera.matrix(shader, "camMatrix");

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}