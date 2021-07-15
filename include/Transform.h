//
// Created by shubh on 7/15/21.
//

#ifndef SHADEGL_TRANSFORM_H
#define SHADEGL_TRANSFORM_H

#include <Mesh.h>
#include <glm/gtx/transform.hpp>

class Transform {
public:
    Transform()
    {
        pos = glm::vec3();
        rot = glm::vec3();
        scale = glm::vec3(1.0f,1.0f,1.0f);;
    }
    Transform(const glm::vec3& _pos, const glm::vec3& _rot, const glm::vec3& _scale)
    {
        pos = _pos;
        rot = _rot;
        scale = _scale;
    }

    glm::mat4 model() const;

    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
};


#endif //SHADEGL_TRANSFORM_H
