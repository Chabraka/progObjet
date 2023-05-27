#pragma once

#include <cstdlib>
#include "../OpenGL/OpenGL.hpp"
#include "../Parameters.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Skybox {
    /* --- Attributes --- */
private:
    const float _radius;
    glm::vec3   _center;

    /* --- Methods --- */
public:
    // Constructors
    Skybox(Parameters& params)
        : _radius(params.BOX_SIZE), _center(glm::vec3(0.f)){}; // Only constructor available
    Skybox(float radius, glm::vec3 center) = delete;
    Skybox(Skybox& skybox)                 = delete;

    // Draw
    void drawSkybox(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao, GLuint texture);
};
