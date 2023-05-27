#pragma once

#include <cstdlib>
#include "../OpenGL/OpenGL.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Tracker {
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
    Tracker()
        : _radius(0.6f), _center(glm::vec3(0.f)), _speed(glm::vec3(0.3f)), _acceleration(glm::vec3(0.05f)){};
    Tracker(float radius, glm::vec3 center, glm::vec3 speed, glm::vec3 acceleration)
        : _radius(radius), _center(center), _speed(speed), _acceleration(acceleration){};

    // Getter
    glm::vec3 getTrackerCenter() { return _center; };

    // Draw
    void drawTracker(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao);

    // Restrictions
    void restrictArea(const float border);
    void restrictSpeed(float minSpeed, float maxSpeed);

    // Update
    void updatePosition(Parameters& params);
    void updatePositionTracker(Parameters& params);
};
