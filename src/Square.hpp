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
    void restrictSpeed();
    
    void updatePosition();
    void updateAcc(std::vector<Square> boids, unsigned int i);

};

void drawSquare(Square sqr, p6::Context& ctx);

// a mettre dans le square pour les differents factors
glm::vec2 attraction(glm::vec2 direction);
glm::vec2 repulsion(glm::vec2 direction,float distance);
glm::vec2  adjustSpeed(glm::vec2 acc,glm::vec2 sumSpeed, int numspeedboids);

// pour les boids
void updateBoidsAcc(std::vector<Square>* boids);