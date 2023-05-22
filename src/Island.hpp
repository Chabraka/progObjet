#pragma once

#include <cstdlib>
#include "OpenGL.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Island {
    /* Attributes */
public:
    const glm::float32 _radius;

private:
    glm::vec3 _center;

    /* Methods */
public:
    // Constructors
    Island()
        : _center(glm::vec3(1.0f)), _radius(1.0f){};
    Island(glm::vec3 center, glm::float32 radius)
        : _center(center), _radius(radius){};

    // Draw
    void drawIsland(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao);
    // void drawIsland(const p6::Shader* shader, glm::mat4 ProjMatrix, GLuint vao, const uint nbTriangles);
};