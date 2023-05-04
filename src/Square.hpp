#pragma once

#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Square {
public:
    const glm::float32 _radius;

private:
    glm::vec2 _center;
    glm::vec2 _speed;
    glm::vec2 _acceleration;

public:
    Square(glm::vec2 center, glm::float32 radius, glm::vec2 speed, glm::vec2 acceleration)
        : _center(center), _radius(radius), _speed(speed), _acceleration(acceleration) /*, _maxSpeed(maxSpeed), _minSpeed(minSpeed) */ {};

    // Getters
    glm::vec2 getCenter() const { return _center; };
    glm::vec2 getSpeed() const { return _speed; };
    glm::vec2 getAcceleration() const { return _acceleration; };

    void setSpeed(glm::vec2 speed) { _speed = speed; }; /* passer en private quand on aura une class tracker */

private:
    // Setters
    void setCenter(glm::vec2 center) { _center = center; };
    void setAcceleration(glm::vec2 acceleration) { _acceleration = acceleration; };

    // Restrictions
    void restrictArea();
    void restrictSpeed(float minSpeed, float maxSpeed);

    // Behaviors
    glm::vec2 attraction(glm::vec2 direction, float distance, float factorAttraction);
    glm::vec2 repulsion(glm::vec2 direction, float distance, float factorRepulsion, float maxRepulsion);
    glm::vec2 adjustSpeed(glm::vec2 acc, glm::vec2 sumSpeed, int numspeedboids);

public:
    // Updates
    void updatePosition(float minSpeed, float maxSpeed);
    void updateAcc(std::vector<Square> boids, unsigned int i, float minDistance, float factorAttraction, float factorRepulsion, float maxRepulsion, Square* trackSquare, float factorAttractTracker);

    glm::vec2 attractionTracker(Square* trackSquare, float factorAttractTracker);
};

// Drawing
void drawSquare(Square sqr, p6::Context& ctx);

// Tracker
void updatePositionTracker(Square* trackSquare);