#include "Boid.hpp"
#include <sys/types.h>
#include "../OpenGL/OpenGL.hpp"

/* ----- Draw ----- */
void Boid::drawBoid(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, const GLuint& vao)
{
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
    T           = glm::translate(T, glm::vec3(_center.x / 2, _center.y, _center.z));

    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uColor", glm::vec3(0.5, 0.8, 0.2));

    drawOpenGLBoids(vao);
}

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

    // Speed > 0
    if (currentSpeed > 0.001)
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

glm::vec3 Boid::adjustSpeed(glm::vec3 acc, glm::vec3 sumSpeed, int numspeedboids)
{
    // Adjustment of the speed relative to the neighbors
    if (numspeedboids != 0)
    {
        glm::vec3 boidsSpeedMean = sumSpeed / (float)numspeedboids;
        acc                      = acc + boidsSpeedMean * (float)1.; // parameter to adjust (1) can be a factorSpeedMean
    }
    return acc;
}

/* ----- Updates ----- */

void Boid::updatePosition(Parameters& params)
{
    float dt = 1.0 / 60.;

    // Calcul of the position
    _center.x += _speed.x * dt + _acceleration.x * dt * dt / 2;
    _center.y += _speed.y * dt + _acceleration.y * dt * dt / 2;
    _center.z += _speed.z * dt + _acceleration.z * dt * dt / 2;

    // Calcul of the speed
    _speed.x += _acceleration.x * dt;
    _speed.y += _acceleration.y * dt;
    _speed.z += _acceleration.z * dt;

    // Restrict the position
    restrictSpeed(params.MIN_SPEED, params.MAX_SPEED);
    restrictArea(params.BOX_SIZE);
}

void Boid::updateAcc(std::vector<Boid> boids, unsigned int i, const float& minDistance, const float& factorAttraction, const float& factorRepulsion, const float& maxRepulsion, Tracker* tracker, const float& factorAttractTracker)
{
    glm::vec3 acc(0.);
    glm::vec3 sumSpeed(0.);      // sum speed of neighbors
    int       numspeedboids = 0; // number of neighbors concern by the speed adjustment

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
        // Avoid divison by 0
        if (distance <= 0.001)
        {
            continue;
        }
        glm::vec3 direction = (neighbour->_center - _center) / distance;
        acc += attraction(direction, distance, factorAttraction) + repulsion(direction, distance, factorRepulsion, maxRepulsion);

        if (distance < minDistance)
        { // minimal distance to adjust 0.7 it's a big crowd, 0.2 you have little groups
            // exclude those who are too far away
            sumSpeed = sumSpeed + neighbour->_speed;
            numspeedboids += 1;
        }
    }

    acc += attractionTracker(tracker, factorAttractTracker);

    _acceleration = adjustSpeed(acc, sumSpeed, numspeedboids);
}

glm::vec3 Boid::attractionTracker(Tracker* tracker, const float& factorAttractTracker)
{
    float     distance = glm::distance(_center, tracker->getTrackerCenter());
    glm::vec3 attract(0.);
    // Avoid divison by 0
    if (distance <= 0.001)
    {
        return attract;
    }
    glm::vec3 direction = (tracker->getTrackerCenter() - _center) / distance;
    return attraction(direction, distance, factorAttractTracker);
}
