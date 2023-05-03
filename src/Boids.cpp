#include "Boids.hpp"
#include "Parameters.hpp"

/* ----- Constructor ----- */
Boids::Boids(Parameters& params)
{
    // Creation of boids
    for (int i = 0; i < params.MAX_SQUARE_NB; i++)
    {
        Square square(
            glm::vec2(p6::random::number(-2.f, 2.f), p6::random::number(-1.f, 1.f)),
            0.05f,
            glm::vec2(p6::random::number(-params.MAX_SPEED, params.MAX_SPEED), p6::random::number(-params.MAX_SPEED, params.MAX_SPEED)),
            glm::vec2(0., 0.)
        );
        _boids.push_back(square);
    }
}

/* ----- Draw ----- */
void Boids::drawBoids(p6::Context& ctx, Parameters& params)
{
    for (int j = 0; j < params.SQUARE_NB; j++)
    {
        drawSquare(_boids[j], ctx);
        _boids[j].updatePosition(params.MIN_SPEED, params.MAX_SPEED);
    }
}

/* ----- Updates ----- */
void Boids::updateBoidsAcc(Square* trackSquare, Parameters& params)
{
    for (int i = 0; i < params.SQUARE_NB; i++)
    {
        _boids.at(i).updateAcc(_boids, i, params.MIN_DIST, params.FACTOR_ATTRACTION, params.FACTOR_REPULSION, params.FACTOR_REPULSION, trackSquare, params.FACTOR_ATTRACT_TRACKER);
    }
}
