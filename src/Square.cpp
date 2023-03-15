#include "Square.hpp"

void drawSquare(Square sqr, p6::Context& ctx)
{
    ctx.square(
        p6::Center{sqr.center.x, sqr.center.y},
        p6::Radius{sqr.radius}
    );
    ctx.fill = {1.f, 0.7f, 0.2f};
}