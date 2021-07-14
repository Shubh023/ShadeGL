//
// Created by shubh on 7/14/21.
//

#ifndef SHADEGL_SPHERE_H
#define SHADEGL_SPHERE_H

const GLfloat PI= 3.14159265358979323846f;

std::vector<float> sphereVertices(int xgrid, int ygrid) {
    std::vector<float> vertices;
    for (int y = 0; y <= ygrid; y++) {
        for (int x = 0; x <= xgrid; x++) {
            float xSegment = (float) x / (float) xgrid;
            float ySegment = (float) y / (float) ygrid;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            vertices.push_back(xPos);
            vertices.push_back(yPos);
            vertices.push_back(zPos);
        }
    }
    return vertices;
}

std::vector<int> sphereIndices(int xgrid, int ygrid) {
    std::vector<int> indices;
    for (int i = 0; i < ygrid; i++) {
        for (int j = 0; j < xgrid; j++) {
            indices.push_back(i * (xgrid + 1) + j);
            indices.push_back((i + 1) * (xgrid + 1) + j);
            indices.push_back((i + 1) * (xgrid + 1) + j + 1);
            indices.push_back(i * (xgrid + 1) + j);
            indices.push_back((i + 1) * (xgrid + 1) + j + 1);
            indices.push_back(i * (xgrid + 1) + j + 1);
        }
    }
    return indices;
}


#endif //SHADEGL_SPHERE_H
