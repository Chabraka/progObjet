#include "Tracker.hpp"
#include <sys/types.h>
#include <cstdlib>

/* ----- Draw ----- */
void Tracker::drawTracker(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao)
{
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, -2));
    T           = glm::translate(T, glm::vec3(this->_center.x / 2, this->_center.y, this->_center.z));

    // shader->set("uModelMatrix", T);
    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uColor", glm::vec3(0.8, 0.3, 0.7));

    drawOpenGL(vao);
}

/* --- Restrictions --- */

void Tracker::restrictArea()
{
    /* If the Tracker hits the walls, change direction */

    // Left wall
    if (this->_center.x - this->_radius < -4)
    {
        this->_center.x = -4 + this->_radius;
        this->_speed.x  = -this->_speed.x;
    }

    // Right wall
    else if (this->_center.x + this->_radius > 4)
    {
        this->_center.x = 4 - this->_radius;
        this->_speed.x  = -this->_speed.x;
    }

    // Bottom wall
    if (this->_center.y - this->_radius < -2)
    {
        this->_center.y = -2 + this->_radius;
        this->_speed.y  = -this->_speed.y;
    }

    // Top wall
    else if (this->_center.y + this->_radius > 2)
    {
        this->_center.y = 2 - this->_radius;
        this->_speed.y  = -this->_speed.y;
    }

    // Back wall
    if (this->_center.z - this->_radius < -2)
    {
        this->_center.z = -2 + this->_radius;
        this->_speed.z  = -this->_speed.z;
    }

    // Front wall
    else if (this->_center.z + this->_radius > 2)
    {
        this->_center.z = 2 - this->_radius;
        this->_speed.z  = -this->_speed.z;
    }
}

void Tracker::restrictSpeed(float minSpeed, float maxSpeed)
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

/* --- Update --- */
void Tracker::updatePosition(float minSpeed, float maxSpeed)
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

void Tracker::updatePositionTracker()
{
    double direction_x = p6::random::number(-0.07f, 0.07f);
    double direction_y = p6::random::number(-0.07f, 0.07f);
    double direction_z = p6::random::number(-0.07f, 0.07f);

    glm::vec3 speed(direction_x + this->_speed.x, direction_y + this->_speed.y, direction_z + this->_speed.z);
    this->_speed = speed;

    this->updatePosition(0.1, 0.7);
}