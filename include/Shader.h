//
// Created by shubh on 7/13/21.
//

#ifndef SHADEGL_SHADER_H
#define SHADEGL_SHADER_H

#include <ShadeGL.h>

#include <utility>

class Shader {
public:
    Shader(const char* _fragment, const char* _vertex);
    static unsigned int CompileShader(unsigned int type, const std::string& source);

    // Use or Activate the shader
    void use() { glUseProgram(programID); };

    // Utility uniform functions
    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
    }
    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    }
    void Delete() {
        glDeleteProgram(programID);
    }
    unsigned int programID;
};


#endif //SHADEGL_SHADER_H
