#include "Boid.hpp"
#include <sys/types.h>
#include "../OpenGL/OpenGL.hpp"

/* ----- Restrictions ----- */

void Boid::restrictArea(const float& border)
{
    /* If the Boid hits the walls, change direction */
    // Left wall
    if (_center.x - _radius < -border)
    {
        _center.x = -border + _radius;
        _speed.x  = -_speed.x;
    }
    // Right wall
    else if (_center.x + _radius > border)
    {
        _center.x = border - _radius;
        _speed.x  = -_speed.x;
    }
    // Bottom wall
    if (_center.y - _radius < -border)
    {
        _center.y = -border + _radius;
        _speed.y  = -_speed.y;
    }
    // Top wall
    else if (_center.y + _radius > border)
    {
        _center.y = border - _radius;
        _speed.y  = -_speed.y;
    }
    // Back wall
    if (_center.z - _radius < -border)
    {
        _center.z = -border + _radius;
        _speed.z  = -_speed.z;
    }
    // Front wall
    else if (_center.z + _radius > border)
    {
        _center.z = border - _radius;
        _speed.z  = -_speed.z;
    }
}

void Boid::restrictSpeed(const float& minSpeed, const float& maxSpeed)
{
    float currentSpeed = glm::length(_speed);
    if (currentSpeed > 0.001) // Speed > 0
    {
        if (currentSpeed > maxSpeed)
        {
            _speed = glm::normalize(_speed) * maxSpeed;
        }
        if (currentSpeed < minSpeed)
        {
            _speed = glm::normalize(_speed) * minSpeed;
        }
    }
}

/* ----- Behaviors ----- */

glm::vec3 Boid::attraction(const glm::vec3& direction, const float& distance, const float& factorAttraction)
{
    return direction * factorAttraction / distance;
}

glm::vec3 Boid::repulsion(const glm::vec3& direction, const float& distance, const float& factorRepulsion, const float& maxRepulsion)
{
    return direction * std::max((1 / (distance * distance)) * (0.01f * factorRepulsion), maxRepulsion);
}

glm::vec3 Boid::adjustSpeed(glm::vec3 acc, glm::vec3 sumSpeed, int numSpeedBoids)
{
    // Adjustment of the speed relative to the neighbors
    if (numSpeedBoids != 0)
    {
        glm::vec3 boidsSpeedMean = sumSpeed / (float)numSpeedBoids;
        acc                      = acc + boidsSpeedMean * 1.f; // parameter to adjust (1) can be a factorSpeedMean
    }
    return acc;
}

/* ----- Updates ----- */
void Boid::calculateCollisions(const int& boidsNb, const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland)
{
    // With the main island
    float distance = glm::distance(_center, mainIsland.getCenter());
    if (distance <= (_radius + mainIsland.getRadius() * 2))
    {
        _center += glm::normalize(_center) * glm::vec3(0.006f);
        _speed -= glm::vec3(0.08f);
    }
    // With the other boids
    for (unsigned int j = 0; j < boidsNb; j++)
    {
        float distance = glm::distance(_center, boids[j].getCenter());
        if (distance <= (2 * _radius) && distance != 0)
        {
            _center -= glm::normalize(_center) * glm::vec3(0.001f);
        }
    }
    // With obstacles
    for (unsigned int j = 0; j < islands.size(); j++)
    {
        float distance = glm::distance(_center, islands[j].getCenter());
        if (distance <= (_radius + islands[j].getRadius()))
        {
            _center += glm::normalize(_center) * glm::vec3(0.006f);
            _speed = glm::vec3(0.08f);
        }
    }
}

void Boid::updatePosition(const Parameters& params, float dt, const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland)
{
    // Center position
    _center.x += _speed.x * dt + _acceleration.x * dt * dt / 2;
    _center.y += _speed.y * dt + _acceleration.y * dt * dt / 2;
    _center.z += _speed.z * dt + _acceleration.z * dt * dt / 2;

    // Speed
    _speed.x += _acceleration.x * dt;
    _speed.y += _acceleration.y * dt;
    _speed.z += _acceleration.z * dt;

    // Restrict the position
    restrictSpeed(params.MIN_SPEED, params.MAX_SPEED);
    calculateCollisions(params.BOID_NB, boids, islands, mainIsland);
    restrictArea(params.BOX_SIZE);
}

void Boid::updateAcc(const Parameters& params, std::vector<Boid> boids, unsigned int i)
{
    glm::vec3 acc(0.f);
    glm::vec3 sumSpeed(0.f);     // sum speed of neighbors
    int       numSpeedBoids = 0; // number of neighbors concerned by the speed adjustment

    for (unsigned int j = 0; j < boids.size(); j++)
    {
        /* Itself */
        if (i == j)
        {
            continue;
        }

        /* Neighbors */
        Boid* neighbour = &boids[j];
        float distance  = glm::distance(_center, neighbour->_center);

        if (distance <= 0.001f) // Avoid divison by 0
        {
            continue;
        }
        glm::vec3 direction = (neighbour->_center - _center) / distance;
        acc += attraction(direction, distance, params.FACTOR_ATTRACTION) + repulsion(direction, distance, params.FACTOR_REPULSION, params.MAX_REPULSION);

        // Exclude those who are too far away
        if (distance < params.MIN_DIST) // Minimal distance to adjust : 0.7 it's a big crowd, 0.2 you have little groups
        {
            sumSpeed = sumSpeed + neighbour->_speed;
            numSpeedBoids += 1;
        }
    }
    _acceleration = adjustSpeed(acc, sumSpeed, numSpeedBoids);
}
