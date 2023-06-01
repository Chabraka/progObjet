#pragma once

#include <cstdlib>
#include "../Light.hpp"
#include "../Boids/Boids.hpp"
#include "../Obstacles/Islands.hpp"
#include "../OpenGL/OpenGL.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Walker {
    /* Attributes */
public:
    const float _radius;

private:
	LightProperties _lightProperties;
	Light _lamp;
	float _orientation;
    glm::vec3 _center;
    glm::vec3 _speed;
    ObjRenderer _objboat;
    ObjRenderer _objpirate;

    /* Methods */
public:
    // Constructors
    Walker(const p6::Shader* shader)
        : _radius(0.05f), _center(glm::vec3(0.f)),
          _speed(glm::vec3(0.f)),
          _objboat(ObjRenderer("assets/models/boat1.obj", "assets/textures/Boat_Tex.png", shader)),
          _objpirate(ObjRenderer("assets/models/Pirate.obj", "assets/textures/PirateUVtexture.png", shader)),
		  _lamp(glm::vec3(0,0,0.5f), glm::vec3(0.4,0.25,0.1))
          {}; // Only constructor available
	Walker(const p6::Shader* shader, LightProperties lightprop):Walker(shader){
		_lightProperties = lightprop;
	}
    Walker(float radius, glm::vec3 center) = delete;
    Walker(Walker& walker)                 = delete;

    // Getter
    glm::vec3 getCenter() const { return _center; };
    float getOrientation() const { return _orientation; };

    // Draw
    void drawWalker(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, glm::vec3 lightpos, glm::vec3 lightIntensity);

    // Restrictions
    void restrictArea(const float border);
    void restrictSpeed(float minSpeed, float maxSpeed);
    void calculateCollisions(const std::vector<Boid>& boids, const std::vector<Island>& islands);

	Light getLight();

    // Update
    void updatePosition(const p6::Context& ctx, const float border, const std::vector<Boid>& boids, const std::vector<Island>& islands);
};