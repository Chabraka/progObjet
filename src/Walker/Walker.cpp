#include "Walker.hpp"
#include <sys/types.h>
#include <cstdlib>

/* ----- Draw ----- */
void Walker::drawWalker(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao)
{
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
    T           = glm::translate(T, glm::vec3(this->_center.x / 2, this->_center.y, this->_center.z));

    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uColor", glm::vec3(0.2, 0.3, 0.7));

    drawOpenGL(vao);
}

/* --- Restrictions --- */

void Walker::restrictArea(const float border)
{
    // Left wall
    if (this->_center.x - this->_radius < -border)
    {
        this->_center.x = -border + this->_radius;
        this->_speed.x  = 0.1;
    }

    // Right wall
    else if (this->_center.x + this->_radius > border)
    {
        this->_center.x = border - this->_radius;
        this->_speed.x  = 0.1;
    }

    // Bottom wall
    if (this->_center.y - this->_radius < -border)
    {
        this->_center.y = -border + this->_radius;
        this->_speed.y  = 0.1;
    }

    // Top wall
    else if (this->_center.y + this->_radius > border)
    {
        this->_center.y = border - this->_radius;
        this->_speed.y  = 0.1;
    }

    // Back wall
    if (this->_center.z - this->_radius < -border)
    {
        this->_center.z = -border + this->_radius;
        this->_speed.z  = 0.1;
    }

    // Front wall
    else if (this->_center.z + this->_radius > border)
    {
        this->_center.z = border - this->_radius;
        this->_speed.z  = 0.1;
    }
}

void Walker::restrictSpeed(float minSpeed, float maxSpeed)
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
void Walker::updatePosition(const p6::Context& ctx, const float border)
{
    float dt = ctx.delta_time() * 0.5;

    if (ctx.key_is_pressed(GLFW_KEY_A) || ctx.key_is_pressed(GLFW_KEY_LEFT))
    {
        _center.x -= _speed.x * dt + _acceleration.x * dt * dt * 0.5f;
        _speed.x += _acceleration.x * dt;
    }

    if (ctx.key_is_pressed(GLFW_KEY_D) || ctx.key_is_pressed(GLFW_KEY_RIGHT))
    {
        _center.x += _speed.x * dt + _acceleration.x * dt * dt * 0.5f;
        _speed.x += _acceleration.x * dt;
    }

    if (ctx.key_is_pressed(GLFW_KEY_W) || ctx.key_is_pressed(GLFW_KEY_UP))
    {
        _center.z -= _speed.z * dt + _acceleration.z * dt * dt * 0.5f;
        _speed.z += _acceleration.z * dt;
    }

    if (ctx.key_is_pressed(GLFW_KEY_S) || ctx.key_is_pressed(GLFW_KEY_DOWN))
    {
        _center.z += _speed.z * dt + _acceleration.z * dt * dt * 0.5f;
        _speed.z += _acceleration.z * dt;
    }

    if (ctx.key_is_pressed(GLFW_KEY_SPACE))
    {
        _center.y += _speed.y * dt + _acceleration.y * dt * dt * 0.5f;
        _speed.y += _acceleration.y * dt;
    }
    else
    {
        _center.y -= (_speed.y * dt + _acceleration.y * dt * dt * 0.5f) * 0.5;
        _speed.y += _acceleration.y * dt;
    }

    this->restrictSpeed(0.1, 0.7);
    this->restrictArea(border);
}