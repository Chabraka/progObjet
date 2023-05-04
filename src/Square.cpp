#include "Square.hpp"
#include <sys/types.h>

/* ----- Draw ----- */
void drawSquare(Square sqr, p6::Context& ctx)
{
    ctx.square(
        p6::Center{sqr.getCenter().x, sqr.getCenter().y},
        p6::Radius{sqr._radius}
    );
    ctx.fill = {1.f, 0.7f, 0.2f};
}

/* ----- Restrictions ----- */

void Square::restrictArea()
{
    /* If the square hits the walls, change direction */

    // Left wall
    if (this->getCenter().x - this->_radius < -2)
    {
        this->setCenter(glm::vec2(-2 + this->_radius, this->getCenter().y));
        this->setSpeed(glm::vec2(-this->getSpeed().x, this->getSpeed().y));
    }

    // Right wall
    else if (this->getCenter().x + this->_radius > 2)
    {
        this->setCenter(glm::vec2(2 - this->_radius, this->getCenter().y));
        this->setSpeed(glm::vec2(-this->getSpeed().x, this->getSpeed().y));
    }

    // Bottom wall
    if (this->getCenter().y - this->_radius < -1)
    {
        this->setCenter(glm::vec2(this->getCenter().x, -1 + this->_radius));
        this->setSpeed(glm::vec2(this->getSpeed().x, -this->getSpeed().y));
    }

    // Top wall
    else if (this->getCenter().y + this->_radius > 1)
    {
        this->setCenter(glm::vec2(this->getCenter().x, 1 - this->_radius));
        this->setSpeed(glm::vec2(this->getSpeed().x, -this->getSpeed().y));
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

/* ----- Behaviors ----- */

glm::vec2 Square::attraction(glm::vec2 direction, float distance, float factorAttraction)
{
    return direction * factorAttraction / distance;
}

glm::vec2 Square::repulsion(glm::vec2 direction, float distance, float factorRepulsion, float maxRepulsion)
{
    return direction * std::max((1 / (distance * distance)) * (0.01f * factorRepulsion), maxRepulsion);
}

glm::vec2 Square::adjustSpeed(glm::vec2 acc, glm::vec2 sumSpeed, int numspeedboids)
{
    // Adjustment of the speed relative to the neighbors
    if (numspeedboids != 0)
    {
        glm::vec2 BoidsSpeedMean = sumSpeed / (float)numspeedboids;
        acc                      = acc + BoidsSpeedMean * (float)1.; // parameter to adjust (1) can be a factorSpeedMean
    }
    return acc;
}

/* ----- Updates ----- */

void Square::updatePosition(float minSpeed, float maxSpeed)
{
    float dt = 1.0 / 60.;

    // Calcul of the position
    this->setCenter(this->getCenter() + glm::vec2(this->getSpeed() * dt + this->getAcceleration() * dt * dt * 0.5f));

    // Calcul of the speed
    this->setSpeed(this->getSpeed() + this->getAcceleration() * dt);

    // Restrict the position
    this->restrictSpeed(minSpeed, maxSpeed);
    this->restrictArea();
}

void Square::updateAcc(std::vector<Square> boids, unsigned int i, float minDistance, float factorAttraction, float factorRepulsion, float maxRepulsion, Square* trackSquare, float factorAttractTracker)
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
        acc += attraction(direction, distance, factorAttraction) + repulsion(direction, distance, factorRepulsion, maxRepulsion);

        if (distance < minDistance)
        { // minimal distance to adjust 0.7 it's a big crowd, 0.2 you have little groups
            // exclude those who are too far away
            sumSpeed = sumSpeed + neighbour->_speed;
            numspeedboids += 1;
        }
    }

    acc += attractionTracker(trackSquare, factorAttractTracker);

    this->_acceleration = adjustSpeed(acc, sumSpeed, numspeedboids);
}

/* --- Tracker --- */

void updatePositionTracker(Square* trackSquare)
{
    double direction_x = p6::random::number(-0.07f, 0.07f);
    double direction_y = p6::random::number(-0.07f, 0.07f);

    glm::vec2 speed(direction_x + trackSquare->getSpeed().x, direction_y + trackSquare->getSpeed().y);
    trackSquare->setSpeed(speed);

    trackSquare->updatePosition(0.3, 0.7);
}

glm::vec2 Square::attractionTracker(Square* trackSquare, float factorAttractTracker)
{
    float     distance = glm::distance(this->getCenter(), trackSquare->getCenter());
    glm::vec2 attract(0., 0.);
    // Avoid divison by 0
    if (distance <= 0.001)
    {
        return attract;
    }
    glm::vec2 direction = (trackSquare->getCenter() - this->getCenter()) / distance;
    return attraction(direction, distance, factorAttractTracker);
}
