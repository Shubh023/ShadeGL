//
// Created by shubh on 7/13/21.
//

#ifndef SHADEGL_SHADER_H
#define SHADEGL_SHADER_H

#include <ShadeGL.h>

#include <utility>
#include <vector>

class Shader {
public:
    Shader(const char* _fragment, const char* _vertex);

    static unsigned int compile(unsigned int type, const std::string& source);
    void use() const { glUseProgram(programID); };
    void del() const { glDeleteProgram(programID); }
    unsigned int programID;
};

#endif //SHADEGL_SHADER_H
