#pragma once

#include <cstdlib>
#include "../Tracker.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid {
    /* Attributes */
public:
    const glm::float32 _radius;

private:
    glm::vec3 _center;
    glm::vec3 _speed;
    glm::vec3 _acceleration;

    //Gluint vao;

    /* Methods */
public:
    // Constructors
    Boid()
        : _radius(1.0f), _center(glm::vec3(1.0f)),  _speed(glm::vec3(1.0f)), _acceleration(glm::vec3(1.0f)){};
    Boid(glm::float32 radius, glm::vec3 center,  glm::vec3 speed, glm::vec3 acceleration)
        :  _radius(radius), _center(center), _speed(speed), _acceleration(acceleration){};

    // Draw
    void drawBoid(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao /*, GLuint texture */);

    // Update
    void      updatePosition(float minSpeed, float maxSpeed);
    void      updateAcc(std::vector<Boid> boids, unsigned int i, float minDistance, float factorAttraction, float factorRepulsion, float maxRepulsion, Tracker* tracker, float factorAttractTracker);
    glm::vec3 attractionTracker(Tracker* tracker, float factorAttractTracker);

private:
    // Restrictions
    void restrictArea();
    void restrictSpeed(float minSpeed, float maxSpeed);

    // Behaviours
    glm::vec3 attraction(glm::vec3 direction, float distance, float factorAttraction);
    glm::vec3 repulsion(glm::vec3 direction, float distance, float factorRepulsion, float maxRepulsion);
    glm::vec3 adjustSpeed(glm::vec3 acc, glm::vec3 sumSpeed, int numspeedboids);
};