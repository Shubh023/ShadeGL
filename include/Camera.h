//
// Created by shubh on 7/13/21.
//

#ifndef SHADEGL_CAMERA_H
#define SHADEGL_CAMERA_H

#include <ShadeGL.h>
#include <Shader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera {
public:

    Camera(int _width, int _height, glm::vec3 _position);

    void matrix(float fov, float nearPlane, float farPlane, Shader& shader, const char* uniform);

    void inputs(GLFWwindow* window);

    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);


    int width;
    int height;
    bool firstClick = true;
    float speed = 0.1f;
    float sensitivity = 100.f;
};


#endif //SHADEGL_CAMERA_H
