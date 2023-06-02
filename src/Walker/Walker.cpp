#include "Walker.hpp"

/* ----- Draw ----- */
void Walker::drawWalker(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, glm::vec3 lightpos, glm::vec3 lightIntensity)
{
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
    T           = glm::translate(T, glm::vec3(_center.x, _center.y, _center.z));
    T           = glm::rotate(T, this->_orientation, glm::vec3(0, -1, 0));

    shader->use();
    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uTexture", 0);

    this->_objboat.shader->set("uKd", this->_lightProperties.diffuse);
    this->_objboat.shader->set("uKs", this->_lightProperties.specular);
    this->_objboat.shader->set("uShininess", this->_lightProperties.shininess);
    this->_objboat.shader->set("uSunPosition", lightpos);
    this->_objboat.shader->set("uSunIntensity", lightIntensity);
    this->_objboat.shader->set("uWalkerPosition", this->_lamp.position);
    this->_objboat.shader->set("uWalkerIntensity", this->_lamp.intensity);

    this->_objboat.draw();
    this->_objpirate.draw();
}

/* --- Restrictions --- */

void Walker::restrictArea()
{
    const float border = Parameters::get().BOX_SIZE - 0.08f;

    // Left wall
    if (_center.x - _radius < -border)
    {
        _center.x = -border + _radius;
        _speed.x  = 0.1;
    }
    // Right wall
    else if (_center.x + _radius > border)
    {
        _center.x = border - _radius;
        _speed.x  = 0.1;
    }
    // Bottom wall
    if (_center.y - _radius < -border)
    {
        _center.y = -border + _radius;
        _speed.y  = 0.1;
    }
    // Top wall
    else if (_center.y + _radius > border)
    {
        _center.y = border - _radius;
        _speed.y  = 0.1;
    }
    // Back wall
    if (_center.z - _radius < -border)
    {
        _center.z = -border + _radius;
        _speed.z  = 0.1;
    }
    // Front wall
    else if (_center.z + _radius > border)
    {
        _center.z = border - _radius;
        _speed.z  = 0.1;
    }
}

void Walker::restrictSpeed(const float& minSpeed, const float& maxSpeed)
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

void Walker::calculateCollisions(const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland)
{
    float distance = glm::distance(_center, mainIsland.getCenter());
    if (distance <= (_radius + mainIsland.getRadius()))
    {
        _center -= glm::vec3(0.03f);
        _speed -= 0.005;
    }
    for (int j = 0; j < Parameters::get().BOID_NB; j++)
    {
        /* With boids */
        float distance = glm::distance(_center, boids[j].getCenter());
        if (distance <= (_radius + boids[j]._radius))
        {
            _center -= boids[j].getCenter() * glm::vec3(0.0005f / (distance * distance));
        }
    }
    for (int j = 0; j < (int)islands.size(); j++)
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
void Walker::updatePosition(const p6::Context& ctx, const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland)
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
        _orientation -= 5.0f * dt;
    }

    if (ctx.key_is_pressed(GLFW_KEY_D) || ctx.key_is_pressed(GLFW_KEY_RIGHT))
    {
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
    this->calculateCollisions(boids, islands, mainIsland);
    this->restrictArea();
}

Light Walker::getLight()
{
    return this->_lamp;
}