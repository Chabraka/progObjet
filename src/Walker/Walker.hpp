#pragma once

#include <cstdlib>
#include "../Boids/Boids.hpp"
#include "../Obstacles/Islands.hpp"
#include "../Obstacles/MainIsland.hpp"
#include "../OpenGL/OpenGL.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Walker {
    /* Attributes */
public:
    const float _radius;

private:
    glm::vec3   _center;
    glm::vec3   _speed;
    glm::vec3   _acceleration;
    ObjRenderer _objboat;
    ObjRenderer _objpirate;

    /* Methods */
public:
    // Constructors
    Walker(const p6::Shader* shader)
        : _radius(0.12f), _center(glm::vec3(0.f, 0.f, 1.f)), _speed(glm::vec3(0.3f)), _acceleration(glm::vec3(0.05f)), _objboat(ObjRenderer("assets/models/boat1.obj", "assets/textures/Boat_Tex.png", shader)), _objpirate(ObjRenderer("assets/models/Pirate.obj", "assets/textures/PirateUVtexture.png", shader)){}; // Only constructor available
    Walker(float radius, glm::vec3 center) = delete;
    Walker(Walker& walker)                 = delete;

    // Getter
    glm::vec3 getCenter() const { return _center; };

    // Draw
    void drawWalker(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix);

    // Restrictions
    void restrictArea(const float border);
    void restrictSpeed(float minSpeed, float maxSpeed);
    void calculateCollisions(const int& boidsNb, std::vector<Boid> boids, const std::vector<Island>& islands, const MainIsland& mainIsland);

    // Update
    void updatePosition(const p6::Context& ctx, const Parameters& params, const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland);
};