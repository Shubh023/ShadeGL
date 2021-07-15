//
// Created by shubh on 7/15/21.
//

#include "Transform.h"

glm::mat4 Transform::model() const {
    glm::mat4 p = glm::translate(pos);
    glm::mat4 s = glm::translate(scale);
    glm::mat4 rx = glm::rotate(rot.x, glm::vec3(1,0,0));
    glm::mat4 ry = glm::rotate(rot.y, glm::vec3(0,1,0));
    glm::mat4 rz = glm::rotate(rot.z, glm::vec3(0,0,1));
    glm::mat4 r = rz * ry * rx;

    return p * r * s;
}