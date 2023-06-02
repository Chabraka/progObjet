#pragma once

#include <sys/types.h>
#include <cstdlib>
#include <vector>
#include "../Boids/Boids.hpp"
#include "../Light/Light.hpp"
#include "../Obstacles/Islands.hpp"
#include "../Obstacles/MainIsland.hpp"
#include "../OpenGL/ObjRenderer.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Walker {
    /* Attributes */
public:
    const float _radius;

private:
    glm::vec3       _center;
    glm::vec3       _speed;
    ObjRenderer     _objboat;
    ObjRenderer     _objpirate;
    Light           _lamp;
    LightProperties _lightProperties;
    float           _orientation;

    /* Methods */
public:
    // Constructors
    Walker(const p6::Shader* shader)
        : _radius(0.05f), _center(glm::vec3(0.f, 0.f, 1.f)), _speed(glm::vec3(0.f)), _objboat(ObjRenderer("assets/models/boat1.obj", "assets/textures/Boat_Tex.png", shader)), _objpirate(ObjRenderer("assets/models/Pirate.obj", "assets/textures/PirateUVtexture.png", shader)), _lamp(glm::vec3(0, 0, 0.5f), glm::vec3(0.4, 0.25, 0.1)){};
    Walker(const p6::Shader* shader, LightProperties lightprop)
        : Walker(shader)
    {
        _lightProperties = lightprop;
    }
    Walker(float radius, glm::vec3 center) = delete;
    Walker(Walker& walker)                 = delete;

    // Getter
    glm::vec3 getCenter() const { return _center; };
    float     getOrientation() const { return _orientation; };

    // Draw
    void drawWalker(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, glm::vec3 lightpos, glm::vec3 lightIntensity);

    // Restrictions
    void restrictArea();
    void restrictSpeed(const float& minSpeed, const float& maxSpeed);
    void calculateCollisions(const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland);

    Light getLight();

    // Update
    void updatePosition(const p6::Context& ctx, const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland);
};