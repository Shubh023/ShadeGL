//
// Created by shubh on 7/14/21.
//
#include"VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::link(VBO& VBO, GLuint format, GLuint np, GLenum type, GLsizeiptr sd, void* off) {
    VBO.bind();
    glVertexAttribPointer(format, np, type, GL_FALSE, sd, off);
    glEnableVertexAttribArray(format);
    VBO.unbind();
}

void VAO::bind() {
    glBindVertexArray(ID);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::del() {
    glDeleteVertexArrays(1, &ID);
}