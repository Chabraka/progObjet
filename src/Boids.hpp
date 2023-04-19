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
    Boids(int squareNumber, int maxSquareNumber, float minSpeed, float maxSpeed, float minDistance, float factorAttraction, float factorRepulsion, float maxRepulsion,float factorAttractTracker);

    // Getters
    int   getSquareNumber() { return _squareNumber; };
    int   getMaxSqareNumber() { return _maxSquareNumber; };
    float getMinSpeed() { return _minSpeed; };
    float getMaxSpeed() { return _maxSpeed; };
    float getMinDistance() { return _minDistance; };
    float getFactorAttraction() { return _factorAttraction; };
    float getFactorRepulsion() { return _factorRepulsion; };
    float getMaxRepulsion() { return _maxRepulsion; };

    // Setters
    void setSquareNumber(int squareNumber) { _squareNumber = squareNumber; };
    void setMaxSqareNumber(int maxSquareNumber) { _maxSquareNumber = maxSquareNumber; };
    void setMinSpeed(float minSpeed) { _minSpeed = minSpeed; };
    void setMaxSpeed(float maxSpeed) { _maxSpeed = maxSpeed; };
    void setMinDistance(float minDistance) { _minDistance = minDistance; };
    void getFactorAttraction(float factorAttraction) { _factorAttraction = factorAttraction; };
    void getFactorRepulsion(float factorRepulsion) { _factorRepulsion = factorRepulsion; };
    void getMaxRepulsion(float maxRepulsion) { _maxRepulsion = maxRepulsion; };

    // Drawing
    void drawBoids(p6::Context& ctx);

    // Updates
    void updateBoidsAcc(Square* trackSquare);
};
