#pragma once

#include <cstdlib>
#include <vector>
#include "Square.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boids {
    // private:
public:
    std::vector<Square> _boids;
    int                 _squareNumber;
    int                 _maxSquareNumber;
    float               _minSpeed;
    float               _maxSpeed;
    float               _minDistance;
    float               _factorAttraction;
    float               _factorRepulsion;
    float               _maxRepulsion;
    float               _factorAttractTracker;

public:
    Boids(int squareNumber, int maxSquareNumber, float minSpeed, float maxSpeed, float minDistance, float factorAttraction, float factorRepulsion, float maxRepulsion, float factorAttractTracker);

    // Getters
    int   getSquareNumber() const { return _squareNumber; };
    int   getMaxSqareNumber() const { return _maxSquareNumber; };
    float getMinSpeed() const { return _minSpeed; };
    float getMaxSpeed() const { return _maxSpeed; };
    float getMinDistance() const { return _minDistance; };
    float getFactorAttraction() const { return _factorAttraction; };
    float getFactorRepulsion() const { return _factorRepulsion; };
    float getMaxRepulsion() const { return _maxRepulsion; };

    // Setters
    void setSquareNumber(int squareNumber) { _squareNumber = squareNumber; };
    void setMaxSqareNumber(int maxSquareNumber) { _maxSquareNumber = maxSquareNumber; };
    void setMinSpeed(float minSpeed) { _minSpeed = minSpeed; };
    void setMaxSpeed(float maxSpeed) { _maxSpeed = maxSpeed; };
    void setMinDistance(float minDistance) { _minDistance = minDistance; };
    void setFactorAttraction(float factorAttraction) { _factorAttraction = factorAttraction; };
    void setFactorRepulsion(float factorRepulsion) { _factorRepulsion = factorRepulsion; };
    void setMaxRepulsion(float maxRepulsion) { _maxRepulsion = maxRepulsion; };

    // Drawing
    void drawBoids(p6::Context& ctx);

    // Updates
    void updateBoidsAcc(Square* trackSquare);
};
