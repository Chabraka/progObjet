#include "Square.hpp"

void drawSquare(Square sqr, p6::Context& ctx)
{
    ctx.square(
        p6::Center{sqr.center.x, sqr.center.y},
        p6::Radius{sqr.radius}
    );
    ctx.fill = {1.f, 0.7f, 0.2f};
}

void Square::updatePosition(p6::Context& ctx)
{
    double dt = 1.0 / 60;

    if (abs(this->center.x + this->radius) < 2 && abs(this->center.y + this->radius) < 1)
    {
        this->speed.x += this->acc.x * dt;
        this->speed.y += this->acc.y * dt;
        this->center.x += this->speed.x * dt;
        this->center.y += this->speed.y * dt;
    }
    else
    {
        this->center.x = 0.9;
        this->center.y = -0.5;
    }

    this->speed.x += this->acc.x * dt;
    this->speed.y += this->acc.y * dt;
    this->center.x += this->speed.x * dt;
    this->center.y += this->speed.y * dt;
}