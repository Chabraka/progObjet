#include "Walker.hpp"
#include <sys/types.h>
#include <cstdlib>
#include <vector>

/* ----- Draw ----- */
void Walker::drawWalker(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, glm::vec3 lightpos, glm::vec3 lightIntensity)
{
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
    T           = glm::translate(T, this->getCenter());

    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uTexture", 0);

    this->_objboat.draw();
    this->_objpirate.draw();
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

void Walker::calculateCollisions(const int& boidsNb, const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland)
{
    float distance = glm::distance(_center, mainIsland.getCenter());
    if (distance <= (_radius + mainIsland.getRadius()))
    {
        _center -= glm::vec3(0.03f);
        _speed -= 0.005;
    }
    for (unsigned int j = 0; j < boidsNb; j++)
    {
        /* With boids */
        float distance = glm::distance(_center, boids[j].getCenter());
        if (distance <= (_radius + boids[j]._radius))
        {
            _center -= boids[j].getCenter() * glm::vec3(0.0005f / (distance * distance));
        }
    }
    for (unsigned int j = 0; j < islands.size(); j++)
    {
        /* With obstacles */
        float distance = glm::distance(_center, islands[j].getCenter());
        if (distance <= (_radius + islands[j].getRadius()))
        {
            _center -= islands[j].getCenter() * glm::vec3(0.0005f / (distance * distance));
            _speed -= 0.005;
        }
    }
}

/* --- Update --- */
void Walker::updatePosition(const p6::Context& ctx, const float border, const Parameters& params, const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland)
{
    float     dt = ctx.delta_time() * 0.5;
    glm::vec3 acceleration(0.0, 0.0, 0.0);
    acceleration -= _speed * 5.0f;

    if (ctx.mouse_button_is_pressed(p6::Button::Left))
    {
        _orientation += ctx.mouse_delta().x;
    }

    float r_orientation = _orientation;

    if (ctx.key_is_pressed(GLFW_KEY_A) || ctx.key_is_pressed(GLFW_KEY_LEFT))
    {
        // acceleration -=  20.0f * glm::vec3(cos(r_orientation) * 0.5f, 0.0 , sin(r_orientation) * 0.5f);
        _orientation -= 5.0f * dt;
    }

    if (ctx.key_is_pressed(GLFW_KEY_D) || ctx.key_is_pressed(GLFW_KEY_RIGHT))
    {
        // acceleration +=  20.0f * glm::vec3(cos(r_orientation) * 0.5f, 0.0 , sin(r_orientation) * 0.5f);
        _orientation += 5.0 * dt;
    }

    if (ctx.key_is_pressed(GLFW_KEY_W) || ctx.key_is_pressed(GLFW_KEY_UP))
    {
        acceleration -= 10.0f * glm::vec3(-sin(r_orientation) * 0.5f, 0.0, cos(r_orientation) * 0.5f);
    }

    if (ctx.key_is_pressed(GLFW_KEY_S) || ctx.key_is_pressed(GLFW_KEY_DOWN))
    {
        acceleration += 10.0f * glm::vec3(-sin(r_orientation) * 0.5f, 0.0, cos(r_orientation) * 0.5f);
    }

    if (ctx.key_is_pressed(GLFW_KEY_SPACE))
    {
        acceleration.y += 10.0f;
    }

    if (ctx.shift())
    {
        acceleration.y -= 10.0f;
    }

    _center += _speed * dt + acceleration * dt * dt;
    _speed += acceleration * dt;

    this->restrictSpeed(0.001, 1.);
    this->calculateCollisions(boids.size(), boids, islands, mainIsland);
    this->restrictArea(border);
}

Light Walker::getLight()
{
    return this->_lamp;
}