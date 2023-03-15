#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"

struct Square {
    glm::vec2    center;
    glm::float32 radius;

    Square(glm::vec2 c, glm::float32 r)
        : center(c), radius(r){};
};

void drawSquare(Square sqr, p6::Context& ctx);