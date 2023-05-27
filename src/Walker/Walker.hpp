#pragma once

#include <cstdlib>
#include "../Boids/Boids.hpp"
#include "../Obstacles/Islands.hpp"
#include "../OpenGL/OpenGL.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Walker {
    /* Attributes */
public:
    const float _radius;

private:
    glm::vec3 _center;
    glm::vec3 _speed;
    glm::vec3 _acceleration;

    /* Methods */
public:
    // Constructors
    Walker()
        : _radius(0.05f), _center(glm::vec3(0.f)), _speed(glm::vec3(0.3f)), _acceleration(glm::vec3(0.05f)){}; // Only constructor available
    Walker(float radius, glm::vec3 center) = delete;
    Walker(Walker& walker)                 = delete;

    // Getter
    glm::vec3 getCenter() const { return _center; };

    // Draw
    void drawWalker(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao);

    // Restrictions
    void restrictArea(const float border);
    void restrictSpeed(float minSpeed, float maxSpeed);
    void calculateCollisions(const std::vector<Boid>& boids, const std::vector<Island>& islands);

    // Update
    void updatePosition(const p6::Context& ctx, const float border, const std::vector<Boid>& boids, const std::vector<Island>& islands);
};
