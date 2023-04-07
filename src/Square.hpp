#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Square {
public:
    glm::vec2    center;
    glm::float32 radius;
    glm::vec2    speed;
    glm::vec2    acc;

    float maxSpeed;
    float minSpeed;


    Square(glm::vec2 c, glm::float32 r, glm::vec2 s, glm::vec2 a, float maxS, float minS)
        : center(c), radius(r), speed(s), acc(a), maxSpeed(maxS), minSpeed(minS){};

    void restrictArea();
    void updatePosition();
    void updateAcc(std::vector<Square> boids, unsigned int i);
    void checkCollision(std::vector<Square> boids, unsigned int i);
};

void drawSquare(Square sqr, p6::Context& ctx);

//poour les boids
void updateBoidsAcc(std::vector<Square> *boids);
void checkCollisions(std::vector<Square> *boids);