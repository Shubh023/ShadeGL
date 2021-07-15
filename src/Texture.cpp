//
// Created by shubh on 7/14/21.
//

#include <Texture.h>
Texture::Texture(const char* _path, const char* _tex_type, GLenum _tex_id, GLenum _format, GLenum _data_type)
:   type(_tex_type), tex_id(_tex_id)
{
    int W, H, C;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(_path, &W, &H, &C, 0);
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + tex_id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT_ARB); // GL_REPEAT
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, _format, _data_type, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::assign_unit(Shader& shader, const char* uniform, GLuint tex_id)
{
    GLuint texture_uniform = glGetUniformLocation(shader.programID, uniform);
    shader.use();
    glUniform1i(texture_uniform, tex_id);
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0 + tex_id);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::del()
{
    glDeleteTextures(1, &id);
}