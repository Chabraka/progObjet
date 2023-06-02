#pragma once

#include <sys/types.h>
#include <cstdlib>
#include "../OpenGL/SkyboxOpenGL.hpp"
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
    Skybox()
        : _radius(Parameters::get().BOX_SIZE), _center(glm::vec3(0.f)){}; // Only constructor available
    Skybox(float radius, glm::vec3 center) = delete;
    Skybox(Skybox& skybox)                 = delete;

    // Draw
    void drawSkybox(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, const GLuint& vao, const GLuint& texture);
};
