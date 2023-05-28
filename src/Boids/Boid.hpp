#pragma once

#include <cstdlib>
#include "../Tracker/Tracker.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid {
    /* Attributes */
public:
    const float _radius;
    glm::vec3 _center;

private:
    
    glm::vec3 _speed;
    glm::vec3 _acceleration;

    /* Methods */
public:
    // Constructors
    Boid()
        : _radius(0.05f), _center(glm::vec3(1.0f)), _speed(glm::vec3(0.5f)), _acceleration(glm::vec3(0.5f))
        {};
    Boid(float radius, glm::vec3 center, glm::vec3 speed, glm::vec3 acceleration)
        : _radius(radius), _center(center), _speed(speed), _acceleration(acceleration){};


     // Getter
    glm::vec3 getCenter() const { return _center; };

    // Update
    void      updatePosition(Parameters& params, float dt);
    void      updateAcc(std::vector<Boid> boids, unsigned int i, const float& minDistance, const float& factorAttraction, const float& factorRepulsion, const float& maxRepulsion, Tracker* tracker, const float& factorAttractTracker);
    glm::vec3 attractionTracker(Tracker* tracker, const float& factorAttractTracker);

    private:
    // Restrictions
    void restrictArea(const float& border);
    void restrictSpeed(const float& minSpeed, const float& maxSpeed);

    // Behaviours
    glm::vec3 attraction(const glm::vec3& direction, const float& distance, const float& factorAttraction);
    glm::vec3 repulsion(const glm::vec3& direction, const float& distance, const float& factorRepulsion, const float& maxRepulsion);
    glm::vec3 adjustSpeed(glm::vec3 acc, glm::vec3 sumSpeed, int numspeedboids);
};