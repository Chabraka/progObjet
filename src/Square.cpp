#include "Square.hpp"
#include <sys/types.h>

/* ----- Draw ----- */
void drawSquare(Square sqr, p6::Context& ctx)
{
    ctx.square(
        p6::Center{sqr.getCenter().x, sqr.getCenter().y},
        p6::Radius{sqr.getRadius()}
    );
    ctx.fill = {1.f, 0.7f, 0.2f};
}

// rajouter mouvement aléatoire ?

/* ----- Restrictions ----- */

void Square::restrictArea()
{
    /* If the square hits the walls, change direction */

    // Left wall
    if (this->_center.x - this->_radius < -2)
    {
        this->_center.x = -2 + this->_radius;
        this->_speed.x  = -this->_speed.x;
    }

    // Right wall
    else if (this->_center.x + this->_radius > 2)
    {
        this->_center.x = 2 - this->_radius;
        this->_speed.x  = -this->_speed.x;
    }

    // Bottom wall
    if (this->_center.y - this->_radius < -1)
    {
        this->_center.y = -1 + this->_radius;
        this->_speed.y  = -this->_speed.y;
    }

    // Top wall
    else if (this->_center.y + this->_radius > 1)
    {
        this->_center.y = 1 - this->_radius;
        this->_speed.y  = -this->_speed.y;
    }
}

void Square::restrictSpeed(float minSpeed, float maxSpeed)
{
    float currentSpeed = glm::length(this->_speed);

    // Speed > 0
    if (currentSpeed > 0.001)
    {
        if (currentSpeed > maxSpeed)
        {
            this->_speed = glm::normalize(this->_speed) * maxSpeed;
        }
        if (currentSpeed < minSpeed)
        {
            this->_speed = glm::normalize(this->_speed) * minSpeed;
        }
    }
}

/* ----- Updates ----- */

void Square::updatePosition(float minSpeed, float maxSpeed)
{
    double dt = 1.0 / 60;

    // Calcul of the position
    this->_center.x += this->_speed.x * dt + this->_acceleration.x * dt * dt / 2;
    this->_center.y += this->_speed.y * dt + this->_acceleration.y * dt * dt / 2;

    // Calcul of the speed
    this->_speed.x += this->_acceleration.x * dt;
    this->_speed.y += this->_acceleration.y * dt;

    // Restrict the position
    this->restrictSpeed(minSpeed, maxSpeed);
    this->restrictArea();
}

void Square::updateAcc(std::vector<Square> boids, unsigned int i)
{
    glm::vec2 acc(0., 0.);
    glm::vec2 sumSpeed(0., 0.);  // sum speed of neighbors
    int       numspeedboids = 0; // number of neighbors concern by the speed adjustment

    for (unsigned int j = 0; j < boids.size(); j++)
    {
        /* Itself */
        if (i == j)
        {
            continue;
        }

        /* Neighbors */
        Square* neighbour = &boids[j];
        float   distance  = glm::distance(this->_center, neighbour->_center);
        // Avoid divison by 0
        if (distance <= 0.001)
        {
            continue;
        }
        glm::vec2 direction = (neighbour->_center - this->_center) / distance;
        acc += attraction(direction) + repulsion(direction, distance);
        const float minDistance = 0.7;
        if (distance < minDistance)
        { // minimal distance to adjust 0.7 it's a big crowd, 0.2 you have little groups
            // exclude those who are too far away
            sumSpeed = sumSpeed + neighbour->_speed;
            numspeedboids += 1;
        }
    }

    this->_acceleration = adjustSpeed(acc, sumSpeed, numspeedboids);
}

/* ----- Behaviors ----- */

glm::vec2 attraction(glm::vec2 direction)
{
    const float factorAttraction = 0.0004;
    return direction * factorAttraction;
}

glm::vec2 repulsion(glm::vec2 direction, float distance)
{
    const float factorRepulsion = -0.0002;
    float       maxRepulsion    = -3.;
    return direction * std::max((1 / (distance * distance)) * factorRepulsion, maxRepulsion);
}

glm::vec2 adjustSpeed(glm::vec2 acc, glm::vec2 sumSpeed, int numspeedboids)
{
    // Adjustment of the speed relative to the neighbors
    if (numspeedboids != 0)
    {
        glm::vec2 BoidsSpeedMean = sumSpeed / (float)numspeedboids;
        acc                      = acc + BoidsSpeedMean * (float)1.; // parameter to adjust (1) can be a factorSpeedMean
    }
    return acc;
}

/* ----- Boids ----- */
/*
void updateBoidsAcc(std::vector<Square>* boids)
{
    for (unsigned int i = 0; i < boids->size(); i++)
    {
        boids->at(i).updateAcc(*boids, i);
    }
}
*/
