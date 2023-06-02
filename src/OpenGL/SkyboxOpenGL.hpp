#pragma once

#include <cstddef>
#include <cstdlib>
#include <vector>
#include "../Skybox/Skybox.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "img/src/Image.h"
#include "p6/p6.h"

glm::mat4 translate(float tx, float ty, float tz);

struct Vertex3DUV {
    glm::vec3 _position;
    glm::vec2 _coordTex;
    glm::vec3 _normal;

    Vertex3DUV() = default;
    Vertex3DUV(glm::vec3 p, glm::vec2 c, glm::vec3 n)
        : _position(p), _coordTex(c), _normal(n){};
};

struct MatrixView {
    glm::mat4 _ProjMatrix;
    glm::mat4 _MMatrix;
    glm::mat4 _MVPMatrix;
    glm::mat4 _NormalMatrix;

    MatrixView()
        : _ProjMatrix(glm::perspective(glm::radians(70.f), 1.77f, 0.1f, 100.f)), _MMatrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -2.f))), _NormalMatrix(glm::transpose(glm::inverse(_MMatrix))){};

    void setMatrix();
};

GLuint initOpenGLSkybox(const float& skyboxRadius);
GLuint initTex(const img::Image& image);

void drawOpenGLSkybox(GLuint vao, GLuint texture);