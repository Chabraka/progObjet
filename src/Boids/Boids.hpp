#pragma once

#include <cstdlib>
#include <vector>
#include "../Parameters.hpp"
#include "Boid.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boids {
    /* Attributes */
public:
    std::vector<Boid> _boids;
    MultiResObjRenderer renderer;

    /* Methods */
public:
    // Constructors
    Boids() = default;
    Boids(Parameters& params, float floor_low_medium, float floor_medium_high, const p6::Shader* shader);

    // Draw
    void drawBoids(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, Parameters& params, float dt, glm::vec3 cam_position);

    void drawBoid(Boid *boid, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, float cam_distance);

    // Update
    void updateBoidsAcc(Tracker* tracker, Parameters& params);
};
