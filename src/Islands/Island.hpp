#pragma once

#include <cstdlib>
#include "../OpenGL/OpenGL.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Island {
    /* Attributes */
private:
    glm::vec3 _center;

    /* Methods */
public:
    // Constructors
    Island()
        : _center(glm::vec3(1.0f)){};
    Island(glm::vec3 center)
        : _center(center){};

    // Draw
    void drawIsland(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao);
};