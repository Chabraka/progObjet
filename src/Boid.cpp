#include "Boid.hpp"
#include <sys/types.h>
#include "OpenGL.hpp"

/* ----- Draw ----- */
void Boid::drawBoid(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao)
{
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, -2));
    T           = glm::translate(T, glm::vec3(this->_center.x / 2, this->_center.y, this->_center.z));

    // shader->set("uModelMatrix", T);
    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uColor", glm::vec3(0.5, 0.8, 0.2));

    drawOpenGLBoid(vao);
}

/* ----- Restrictions ----- */

void Boid::restrictArea()
{
    /* If the Boid hits the walls, change direction */

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

    // Back wall
    if (this->_center.z - this->_radius < -1)
    {
        this->_center.z = -1 + this->_radius;
        this->_speed.z  = -this->_speed.z;
    }

    // Front wall
    else if (this->_center.z + this->_radius > 1)
    {
        this->_center.z = 1 - this->_radius;
        this->_speed.z  = -this->_speed.z;
    }
}

void Boid::restrictSpeed(float minSpeed, float maxSpeed)
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

glm::vec3 Boid::attraction(glm::vec3 direction, float distance, float factorAttraction)
{
    return direction * factorAttraction / distance;
}

glm::vec3 Boid::repulsion(glm::vec3 direction, float distance, float factorRepulsion, float maxRepulsion)
{
    return direction * std::max((1 / (distance * distance)) * (0.01f * factorRepulsion), maxRepulsion);
}

glm::vec3 Boid::adjustSpeed(glm::vec3 acc, glm::vec3 sumSpeed, int numspeedboids)
{
    // Adjustment of the speed relative to the neighbors
    if (numspeedboids != 0)
    {
        glm::vec3 BoidsSpeedMean = sumSpeed / (float)numspeedboids;
        acc                      = acc + BoidsSpeedMean * (float)1.; // parameter to adjust (1) can be a factorSpeedMean
    }
    return acc;
}

/* ----- Updates ----- */

void Boid::updatePosition(float minSpeed, float maxSpeed)
{
    float dt = 1.0 / 60.;

    // Calcul of the position
    this->_center.x += this->_speed.x * dt + this->_acceleration.x * dt * dt / 2;
    this->_center.y += this->_speed.y * dt + this->_acceleration.y * dt * dt / 2;
    this->_center.z += this->_speed.z * dt + this->_acceleration.z * dt * dt / 2;

    // Calcul of the speed
    this->_speed.x += this->_acceleration.x * dt;
    this->_speed.y += this->_acceleration.y * dt;
    this->_speed.z += this->_acceleration.z * dt;

    // Restrict the position
    this->restrictSpeed(minSpeed, maxSpeed);
    this->restrictArea();
}

void Boid::updateAcc(std::vector<Boid> boids, unsigned int i, float minDistance, float factorAttraction, float factorRepulsion, float maxRepulsion, Tracker* tracker, float factorAttractTracker)
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
        float distance  = glm::distance(this->_center, neighbour->_center);
        // Avoid divison by 0
        if (distance <= 0.001)
        {
            continue;
        }
        glm::vec3 direction = (neighbour->_center - this->_center) / distance;
        acc += attraction(direction, distance, factorAttraction) + repulsion(direction, distance, factorRepulsion, maxRepulsion);

        if (distance < minDistance)
        { // minimal distance to adjust 0.7 it's a big crowd, 0.2 you have little groups
            // exclude those who are too far away
            sumSpeed = sumSpeed + neighbour->_speed;
            numspeedboids += 1;
        }
    }

    acc += attractionTracker(tracker, factorAttractTracker);

    this->_acceleration = adjustSpeed(acc, sumSpeed, numspeedboids);
}

glm::vec3 Boid::attractionTracker(Tracker* tracker, float factorAttractTracker)
{
    float     distance = glm::distance(this->_center, tracker->getTrackerCenter());
    glm::vec3 attract(0.);
    // Avoid divison by 0
    if (distance <= 0.001)
    {
        return attract;
    }
    glm::vec3 direction = (tracker->getTrackerCenter() - this->_center) / distance;
    return attraction(direction, distance, factorAttractTracker);
}
