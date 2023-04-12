#include "Boids.hpp"

/* ----- Constructor ----- */
Boids::Boids(int squareNumber, int maxSquareNumber, float minSpeed, float maxSpeed, float minDistance, float factorAttraction, float factorRepulsion, float maxRepulsion)
    : _squareNumber(squareNumber), _maxSquareNumber(maxSquareNumber), _minSpeed(minSpeed), _maxSpeed(maxSpeed), _minDistance(minDistance), _factorAttraction(factorAttraction), _factorRepulsion(factorRepulsion), _maxRepulsion(maxRepulsion)
{
    // Creation of boids
    for (int i = 0; i < maxSquareNumber; i++)
    {
        Square square(
            glm::vec2(p6::random::number(-2.f, 2.f), p6::random::number(-1.f, 1.f)),
            0.05f,
            glm::vec2(p6::random::number(-maxSpeed, maxSpeed), p6::random::number(-maxSpeed, maxSpeed)),
            glm::vec2(0., 0.)
            /*
            0.3,
            0.1
            */
        );
        _boids.push_back(square);
    }
};

/* ----- Draw ----- */
void Boids::drawBoids(p6::Context& ctx)
{
    for (unsigned int j = 0; j < _squareNumber; j++)
    {
        drawSquare(_boids[j], ctx);
        _boids[j].updatePosition(_minSpeed, _maxSpeed);
    }
}

/* ----- Updates ----- */
void Boids::updateBoidsAcc()
{
    for (unsigned int i = 0; i < _squareNumber; i++)
    {
        _boids.at(i).updateAcc(_boids, i);
    }
}
