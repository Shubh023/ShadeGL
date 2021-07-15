//
// Created by shubh on 7/14/21.
//
#include"VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::link(VBO& VBO, GLuint format, GLuint np, GLenum type, GLsizeiptr sd, void* off)
{
    VBO.bind();
    glVertexAttribPointer(format, np, type, GL_FALSE, sd, off);
    glEnableVertexAttribArray(format);
    VBO.unbind();
}

// Binds the VAO
void VAO::bind()
{
    glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::unbind()
{
    glBindVertexArray(0);
}

// Deletes the VAO
void VAO::del()
{
    glDeleteVertexArrays(1, &ID);
}