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
    Camera(int _width, int _height, glm::vec3 _position, float speed, float sensitivity);

    void matrix(Shader &shader, const char *uniform);
    void movements(GLFWwindow* window);
    void update(float fov, float near, float far);

    glm::vec3 P;
    glm::vec3 O = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 U = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 CM = glm::mat4(1.0f);
    int width, height;
    bool initial = true;
    float speed = 0.1f, sensitivity = 100.f;
};


#endif //SHADEGL_CAMERA_H
