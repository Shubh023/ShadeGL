//
// Created by shubh on 7/13/21.
//

#include "Shader.h"

#include <utility>

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error Handling on this Shader
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" <<
                  (type == GL_VERTEX_SHADER ? " vertex " : " fragment ") << "shader !" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

Shader::Shader(const char* fragment, const char* vertex) {

    std::ifstream in_file;

    // Load Vertex Shader
    std::string temp;
    std::string vertexShader;
    in_file.open(vertex);
    if (in_file.is_open())
    {
        while(std::getline(in_file, temp))
        {
            vertexShader += temp + "\n";
        }
    }
    else
        std::cout << "Failed to load shaders" << std::endl;
    in_file.close();

    // Load Fragment Shader
    std::string fragmentShader;
    in_file.open(fragment);
    if (in_file.is_open())
    {
        while (std::getline(in_file, temp))
        {
            fragmentShader += temp + "\n";
        }
    }
    else
        std::cout << "Failed to load shaders" << std::endl;
    in_file.close();

    // Create Program and Compile Shaders
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    programID = program;
}