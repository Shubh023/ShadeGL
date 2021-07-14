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
    GLuint ID;
    const char*  type;
    GLuint unit;

    Texture(const char* image, const char* texType, GLenum slot, GLenum format, GLenum pixelType);

    // Assigns a texture unit to a texture
    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    // Binds a texture
    void Bind();
    // Unbinds a texture
    void Unbind();
    // Deletes a texture
    void Delete();
};


#endif //SHADEGL_TEXTURE_H
