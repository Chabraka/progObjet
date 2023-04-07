#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Square {
public:
    glm::vec2    _center;
    glm::float32 _radius;
    glm::vec2    _speed;
    glm::vec2    _acc;

    float _maxSpeed;
    float _minSpeed;

    Square(glm::vec2 c, glm::float32 r, glm::vec2 s, glm::vec2 a, float maxS, float minS)
        : _center(c), _radius(r), _speed(s), _acc(a), _maxSpeed(maxS), _minSpeed(minS){};

    void restrictArea();
    void updatePosition();
    void updateAcc(std::vector<Square> boids, unsigned int i);
    void checkCollision(std::vector<Square> boids, unsigned int i);
};

void drawSquare(Square sqr, p6::Context& ctx);

// poour les boids
void updateBoidsAcc(std::vector<Square>* boids);