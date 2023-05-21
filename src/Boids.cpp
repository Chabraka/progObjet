#include "Boids.hpp"
#include "Parameters.hpp"

/* ----- Constructor ----- */
Boids::Boids(Parameters& params)
{
    // Creation of boids
    for (int i = 0; i < params.MAX_BOID_NB; i++)
    {
        // Boid boid(
        //     glm::vec3(p6::random::number(-2.f, 2.f), p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f)),
        //     0.05f,
        //     glm::vec3(p6::random::number(-params.MAX_SPEED, params.MAX_SPEED), p6::random::number(-params.MAX_SPEED, params.MAX_SPEED), p6::random::number(-params.MAX_SPEED, params.MAX_SPEED)),
        //     glm::vec3(0.)
        // );
        Boid boid(
            glm::vec3(0,0,0),
            0.05f,
            glm::vec3(0,0,0),
            glm::vec3(0.)
        );
        _boids.push_back(boid);
    }
}

/* ----- Draw ----- */
void Boids::drawBoids(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao, Parameters& params)
{
    // for (int j = 0; j < params.BOID_NB; j++)
    for (int j = 0; j < 1; j++)
    {
        _boids[j].drawBoid(shader, ProjMatrix, ViewMatrix, vao);
        _boids[j].updatePosition(params.MIN_SPEED, params.MAX_SPEED);
    }
}

/* ----- Updates ----- */
void Boids::updateBoidsAcc(Tracker* tracker, Parameters& params)
{
    for (int i = 0; i < params.BOID_NB; i++)
    {
        _boids.at(i).updateAcc(_boids, i, params.MIN_DIST, params.FACTOR_ATTRACTION, params.FACTOR_REPULSION, params.FACTOR_REPULSION, tracker, params.FACTOR_ATTRACT_TRACKER);
    }
}
