#include "Square.hpp"

void drawSquare(Square sqr, p6::Context& ctx)
{
    ctx.square(
        p6::Center{sqr.center.x, sqr.center.y},
        p6::Radius{sqr.radius}
    );
    ctx.fill = {1.f, 0.7f, 0.2f};
}

/*Add max speed faire fonction get, set */

void Square::updatePosition()
{
    double dt = 1.0 / 60;

    // Move the square in a random direction
    int direction_x = rand() % 2 == 0 ? -1 : 1;
    int direction_y = rand() % 2 == 0 ? -1 : 1;


        // Randomly change direction and speed up or slow down
        if (rand() % 12 == 0)
        {
            direction_x  = -1;
        }
        else if (rand() % 12 == 1)
        {
            direction_y  = -1;
        }
        else if (rand() % 12 == 2)
        {
            direction_x  = 1;
        }
        else if (rand() % 12 == 3)
        {
            direction_y  = 1;
        }

        this->speed.x += direction_x * this->acc.x * dt;
        this->speed.y += direction_y * this->acc.y * dt;
        this->center.x += this->speed.x * dt;
        this->center.y += this->speed.y * dt;

    // If the square hits the walls, change direction and slow down

    if (this->center.x - this->radius < -2)
    {
        this->center.x = -2 + this->radius;
        this->speed.x  = abs(this->speed.x);
    }

    else if (this->center.x + this->radius > 2)
    {
        this->center.x = 2 - this->radius;
        this->speed.x  = -abs(this->speed.x);
    }

    if (this->center.y - this->radius < -1)
    {
        this->center.y = -1 + this->radius;
        this->speed.y  = abs(this->speed.y);
    }
    else if (this->center.y + this->radius > 1)
    {
        this->center.y = 1 - this->radius;
        this->speed.y  = -abs(this->speed.y);
    }
}
