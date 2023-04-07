#include "Square.hpp"

void drawSquare(Square sqr, p6::Context& ctx)
{
    ctx.square(
        p6::Center{sqr._center.x, sqr._center.y},
        p6::Radius{sqr._radius}
    );
    ctx.fill = {1.f, 0.7f, 0.2f};
}

void Square::restrictArea()
{
    // If the square hits the walls, change direction and slow down

    if (this->_center.x - this->_radius < -2)
    {
        this->_center.x = -2 + this->_radius;
        this->_speed.x  = abs(this->_speed.x);
    }

    else if (this->_center.x + this->_radius > 2)
    {
        this->_center.x = 2 - this->_radius;
        this->_speed.x  = -abs(this->_speed.x);
    }

    if (this->_center.y - this->_radius < -1)
    {
        this->_center.y = -1 + this->_radius;
        this->_speed.y  = abs(this->_speed.y);
    }
    else if (this->_center.y + this->_radius > 1)
    {
        this->_center.y = 1 - this->_radius;
        this->_speed.y  = -abs(this->_speed.y);
    }
}

void Square::updatePosition()
{
    double dt = 1.0 / 60;

    this->_center.x += this->_speed.x * dt + this->_acc.x * dt * dt / 2;
    this->_center.y += this->_speed.y * dt + this->_acc.y * dt * dt / 2;

    this->_speed.x += this->_acc.x * dt;
    this->_speed.y += this->_acc.y * dt;

    // max speed

    float currentSpeed = glm::length(this->_speed);
    if (currentSpeed > _maxSpeed)
    {
        this->_speed = glm::normalize(this->_speed) * _maxSpeed;
    }
    if (currentSpeed < _minSpeed)
    {
        this->_speed = glm::normalize(this->_speed) * _minSpeed;
    }
    this->restrictArea();
}

void Square::updateAcc(std::vector<Square> boids, unsigned int i)
{
    glm::vec2 acc(0., 0.);

    for (unsigned int j = 0; j < boids.size(); j++)
    {
        if (i == j)
        {
            continue;
        }

        Square* neighbour = &boids[j];
        float   distance  = glm::distance(this->_center, neighbour->_center);
        if (distance == 0.)
        {
            continue;
        }

        glm::vec2 speedBoids(0., 0.);
        for (unsigned int k = 0; k < boids.size(); k++)
        {
            if (k == j)
            {
                continue;
            }
            speedBoids += this->_speed;
        }
        speedBoids = speedBoids / (float)boids.size() * (float)0.01;

        // glm::vec2 direction = (neighbour->center - this->center)/distance;

        // comportement général grace  a une courbe attirance et séparation

        // glm::vec2 force = direction*(float)(-0.02/(distance+0.01)+0.02);

        glm::vec2 force = speedBoids * (float)(-0.02 / (distance + 0.01) + 0.02);

        acc += force;
    }
    this->_acc = acc;
}

void updateBoidsAcc(std::vector<Square>* boids)
{
    for (unsigned int i = 0; i < boids->size(); i++)
    {
        boids->at(i).updateAcc(*boids, i);
    }
}

void Square::checkCollision(std::vector<Square> boids, unsigned int i)
{
    // rajouter élément dans classe square
    for (unsigned int j = 0; j < boids.size(); j++)
    {
        if (i == j)
        {
            continue;
        }
        Square* neighbour = &boids[j];
        float   distance  = glm::distance(this->_center, neighbour->_center);

        float minDistance = this->_radius * 2.f;
        if (distance < minDistance)
        {
            glm::vec2 direction   = (this->_center - neighbour->_center) / distance;
            float     penetration = minDistance - distance;
            this->_center += direction * penetration * 0.5f;
            neighbour->_center -= direction * penetration * 0.5f;
            this->_speed -= direction * glm::dot(this->_speed, direction) * 0.5f;
            neighbour->_speed -= direction * glm::dot(neighbour->_speed, direction) * 0.5f;
        }
    }
}

void checkCollisions(std::vector<Square>* boids)
{
    for (unsigned int i = 0; i < boids->size(); i++)
    {
        boids->at(i).checkCollision(*boids, i);
    }
}
