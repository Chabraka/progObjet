#include "Square.hpp"

void drawSquare(Square sqr, p6::Context& ctx)
{
    ctx.square(
        p6::Center{sqr.center.x, sqr.center.y},
        p6::Radius{sqr.radius}
    );
    ctx.fill = {1.f, 0.7f, 0.2f};
}


void Square::updatePosition()
{
    double dt = 1.0 / 60;


        this->center.x += this->speed.x * dt + this->acc.x * dt * dt / 2;
        this->center.y += this->speed.y * dt + this->acc.y * dt * dt / 2;

        this->speed.x += this->acc.x * dt;
        this->speed.y +=  this->acc.y * dt;

        //max speed

        float maxSpeed = 0.3;
        float currentSpeed = glm::length(this->speed);
        if(currentSpeed>maxSpeed){
            this->speed = glm::normalize(this->speed)*maxSpeed;
        }

      

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

void Square::updateAcc(std::vector<Square> boids, unsigned int i){

    glm::vec2 acc(0.,0.);

    for(unsigned int j=0; j<boids.size(); j++){

        if(i==j){
            continue;
        }

        Square *neighbour = &boids[j];
        float distance =  glm::distance(this->center, neighbour->center);
        if(distance==0.){
            continue;
        }
        glm::vec2 direction = (neighbour->center - this->center)/distance;

        //comportement général grace  a une courbe attirance et séparation
        glm::vec2 force = direction*(float)(-0.02/(distance+0.01)+0.02);
        acc += force;
    }
    this->acc= acc;
}

/*
void Square::updateAcc(std::vector<Square> boids, unsigned int i) {
    float separationRadius=0.2;
     float alignementRadius=0.7;
     float cohesionRadius=0.7;
     float maxSpeed = 0.3;
     float maxForce = 0.6;


    glm::vec2 separation(0., 0.);
    glm::vec2 alignement(0., 0.);
    glm::vec2 cohesion(0., 0.);
    unsigned int separationCount = 0;
    unsigned int alignementCount = 0;
    unsigned int cohesionCount = 0;

    for (unsigned int j = 0; j < boids.size(); j++) {
        if (i == j) {
            continue;
        }
        Square *neighbour = &boids[j];
        float distance = glm::distance(this->center, neighbour->center);
        if (distance == 0.) {
            continue;
        }

        // Règle de la séparation
        if (distance < separationRadius) {
            glm::vec2 direction = (this->center - neighbour->center) / distance;
            separation += direction;
            separationCount++;
        }

        // Règle de l'alignement
        if (distance < alignementRadius) {
            alignement += neighbour->speed;
            alignementCount++;
        }

        // Règle de la cohésion
        if (distance < cohesionRadius) {
            cohesion += neighbour->center;
            cohesionCount++;
        }
    }

    // Moyennage des vecteurs de direction de chaque règle
    if (separationCount > 0) {
        separation /= (float) separationCount;
        separation = glm::normalize(separation) * maxSpeed;
        glm::vec2 separationForce = (separation - this->speed);
        separationForce = glm::clamp(separationForce, -maxForce, maxForce);
        this->acc += separationForce;
    }

    if (alignementCount > 0) {
        alignement /= (float) alignementCount;
        alignement = glm::normalize(alignement) * maxSpeed;
        glm::vec2 alignementForce = (alignement - this->speed);
        alignementForce = glm::clamp(alignementForce, -maxForce, maxForce);
        this->acc += alignementForce;
    }

    if (cohesionCount > 0) {
        cohesion /= (float) cohesionCount;
        cohesion = cohesion - this->center;
        cohesion = glm::normalize(cohesion) * maxSpeed;
        glm::vec2 cohesionForce = (cohesion - this->speed);
        cohesionForce = glm::clamp(cohesionForce, -maxForce, maxForce);
        this->acc += cohesionForce;
    }
}*/


void updateBoidsAcc(std::vector<Square> *boids){
    for(unsigned int i=0; i<boids->size(); i++){
        boids->at(i).updateAcc(*boids, i);
    }
    
}


void Square::checkCollision(std::vector<Square>boids, unsigned int i) {
    //rajouter élément dans classe square
    for (unsigned int j = 0; j < boids.size(); j++) {
        if (i == j) {
            continue;
        }
        Square* neighbour = &boids[j];
        float distance = glm::distance(this->center, neighbour->center);

        float minDistance = this->radius * 2.f;
        if (distance < minDistance) {
            glm::vec2 direction = (this->center - neighbour->center) / distance;
            float penetration = minDistance - distance;
            this->center += direction * penetration * 0.5f;
            neighbour->center -= direction * penetration * 0.5f;
            this->speed -= direction * glm::dot(this->speed, direction) * 0.5f;
            neighbour->speed -= direction * glm::dot(neighbour->speed, direction) * 0.5f;
        }
    }
}

void checkCollisions(std::vector<Square>* boids) {
    for (unsigned int i = 0; i < boids->size(); i++) {
        boids->at(i).checkCollision(*boids, i);
    }
}

