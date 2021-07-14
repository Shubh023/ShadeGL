//
// Created by shubh on 7/14/21.
//

#include <Texture.h>

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    // Assigns the type of the texture ot the texture object
    type = texType;

    // Stores the width, height, and the number of color channels of the image
    int widthImg, heightImg, numColCh;

    // Reads the image from a file and stores it in bytes
    /*
    auto loaded_img = tifo::load_image(image);
    unsigned char* bytes = loaded_img->get_buffer();
    widthImg = loaded_img->sx;
    heightImg= loaded_img->sy;
    numColCh = loaded_img->length;
     */
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generates an OpenGL texture object
    glGenTextures(1, &ID);
    // Assigns the texture to a Texture Unit
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // Configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all)
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
    float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    // Assigns the image to the OpenGL Texture object
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    // Generates MipMaps
    glGenerateMipmap(texType);

    stbi_image_free(bytes);

    // Unbinds the OpenGL Texture object so that it can't accidentally be modified
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.programID, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.use();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    glBindTexture(type, ID);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}