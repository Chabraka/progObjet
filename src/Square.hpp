#pragma once

#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Square {
    // private:
public:
    glm::vec2    _center;
    glm::float32 _radius;
    glm::vec2    _speed;
    glm::vec2    _acceleration;
    /*
    float        _maxSpeed;
    float        _minSpeed;
    */

public:
    Square(glm::vec2 center, glm::float32 radius, glm::vec2 speed, glm::vec2 acceleration /*, float maxSpeed, float minSpeed */)
        : _center(center), _radius(radius), _speed(speed), _acceleration(acceleration) /*, _maxSpeed(maxSpeed), _minSpeed(minSpeed) */ {};

    // Getters
    glm::vec2    getCenter() const { return _center; };
    glm::float32 getRadius() const { return _radius; };
    glm::vec2    getSpeed() const { return _speed; };
    glm::vec2    getAcceleration() const { return _acceleration; };

    // Setters
    void setCenter(glm::vec2 center) { _center = center; };
    void setRadius(glm::float32 radius) { _radius = radius; };
    void setSpeed(glm::vec2 speed) { _speed = speed; };
    void setAcceleration(glm::vec2 acceleration) { _acceleration = acceleration; };

    // Restrictions
    void restrictArea();
    void restrictSpeed(float minSpeed, float maxSpeed);

    // Updates
    void updatePosition(float minSpeed, float maxSpeed);
    void updateAcc(std::vector<Square> boids, unsigned int i, float minDistance, float factorAttraction, float factorRepulsion, float maxRepulsion, Square* trackSquare, float factorAttractTracker);

    glm::vec2 attractionTracker(Square* trackSquare, float factorAttractTracker);
};

// Drawing
void drawSquare(Square sqr, p6::Context& ctx);

// a mettre dans le square pour les differents factors
// Behaviors

glm::vec2 attraction(glm::vec2 direction, float distance, float factorAttraction);
glm::vec2 repulsion(glm::vec2 direction, float distance, float factorRepulsion, float maxRepulsion);
glm::vec2 adjustSpeed(glm::vec2 acc, glm::vec2 sumSpeed, int numspeedboids);

void updatePositionTracker(Square* trackSquare);