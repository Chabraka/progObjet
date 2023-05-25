#pragma once

#include <cstdlib>
#include "../OpenGL/OpenGL.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Walker {
    /* Attributes */
public:
    const glm::float32 _radius;

private:
    glm::vec3 _center;
    glm::vec3 _speed;
    glm::vec3 _acceleration;

    /* Methods */
public:
    // Constructors
    Walker()
        : _radius(0.6f), _center(glm::vec3(0.f)), _speed(glm::vec3(0.3f)), _acceleration(glm::vec3(0.05f)){}; // Only constructor available
    Walker(glm::float32 radius, glm::vec3 center) = delete;
    Walker(Walker& walker)                        = delete;

    // Getter
    glm::vec3 getCenter() { return _center; };

    // Draw
    void drawWalker(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao);

    // Restrictions
    void restrictArea();
    void restrictSpeed(float minSpeed, float maxSpeed);

    // Update
    void updatePosition(const p6::Context& ctx);
};
