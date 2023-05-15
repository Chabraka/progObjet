#pragma once

#include <cstddef>
#include <cstdlib>
#include "glm/gtc/matrix_transform.hpp"
#include "p6/p6.h"

glm::mat4 translate(float tx, float ty, float tz);

struct Vertex2DColor {
    glm::vec3 _position;
    glm::vec3 _color;

    Vertex2DColor() = default;
    Vertex2DColor(glm::vec3 p, glm::vec3 c)
        : _position(p), _color(c){};
};

struct MatrixView {
    glm::mat4 _ProjMatrix;
    glm::mat4 _MVMatrix;
    glm::mat4 _MVPMatrix = _ProjMatrix * _MVMatrix;
    glm::mat4 _NormalMatrix;

    MatrixView()
        : _ProjMatrix(glm::perspective(glm::radians(70.f), 1.77f, 0.1f, 100.f)), _MVMatrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -2.f))), _NormalMatrix(glm::transpose(glm::inverse(_MVMatrix))){};

    void setMatrix();
};

GLuint initOpenGL();

void drawOpenGL(GLuint vao);