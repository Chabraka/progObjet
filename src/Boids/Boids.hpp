#pragma once

#include <cstdlib>
#include <vector>
#include "../Obstacles/Island.hpp"
#include "../Obstacles/MainIsland.hpp"
#include "../Parameters.hpp"
#include "Boid.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "p6/p6.h"
#include "../Light.hpp"
#include "OpenGL/ObjRenderer.hpp"

class Boids {
    /* Attributes */
public:
    std::vector<Boid>   _boids;
    MultiResObjRenderer renderer;
    LightProperties light;

    /* Methods */
public:
    // Constructors
    Boids() = default;
    Boids(Parameters& params, float floor_low_medium, float floor_medium_high, const p6::Shader* shader);
    Boids(Parameters& params, float floor_low_medium, float floor_medium_high, const p6::Shader* shader, LightProperties light);

    // Draw

    void drawBoids(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, Parameters& params, float dt, glm::vec3 cam_position, const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland, Light sun, Light walker);

    void drawBoid(Boid *boid, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, float cam_distance,  Light sun, Light walker);


    // Update
    void updateBoidsAcc(Tracker* tracker, Parameters& params);
};
