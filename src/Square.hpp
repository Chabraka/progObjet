#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Square {
public:
    glm::vec2    center;
    glm::float32 radius;
    glm::vec2    speed;
    glm::vec2    acc;

    Square(glm::vec2 c, glm::float32 r, glm::vec2 s, glm::vec2 a)
        : center(c), radius(r), speed(s), acc(a){};

    void updatePosition();
};

void drawSquare(Square sqr, p6::Context& ctx);