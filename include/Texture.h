//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_TEXTURE_H
#define SHADEGL_TEXTURE_H

#include <ShadeGL.h>
#include <Shader.h>
#include <stb_image.h>

class Texture {
public:

    Texture(const char* _path, const char* _tex_type, GLenum _tex_id, GLenum _format, GLenum _data_type);

    GLuint id;
    const char*  type;
    GLuint tex_id;

    void assign_unit(Shader& shader, const char* uniform, GLuint tex_id);
    void bind();
    void unbind();
    void del();
};


#endif //SHADEGL_TEXTURE_H
