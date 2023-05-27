#pragma once

#include <cstdlib>
#include "../OpenGL/OpenGL.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Island {
    /* Attributes */
private:
    const float _radius;
    glm::vec3   _center;

    /* Methods */
public:
    // Constructors
    Island()
        : _radius(0.7f), _center(glm::vec3(0.0f)){};
    Island(glm::vec3 center)
        : _radius(0.1f), _center(center){};

    // Draw
    void drawIsland(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao);
};