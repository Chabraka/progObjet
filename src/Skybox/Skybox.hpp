#pragma once

#include <cstdlib>
#include "../OpenGL/OpenGL.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Skybox {
    /* Attributes */
private:
    const glm::float32 _radius;
    glm::vec3          _center;

    /* Methods */
public:
    // Constructors
    Skybox()
        : _radius(2.f), _center(glm::vec3(0.f)){};
    Skybox(glm::float32 radius, glm::vec3 center)
        : _radius(radius), _center(center){};

    // Draw
    void drawSkybox(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao /*, GLuint texture */);
};
