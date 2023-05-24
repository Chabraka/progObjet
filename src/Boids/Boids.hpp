#pragma once

#include <cstdlib>
#include <vector>
#include "Boid.hpp"
#include "Parameters.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boids {
    /* Attributes */
public:
    std::vector<Boid> _boids;

    /* Methods */
public:
    // Constructors
    Boids() = default;
    Boids(Parameters& params);

    // Draw
    void drawBoids(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao, Parameters& params);

    // Update
    void updateBoidsAcc(Tracker* tracker, Parameters& params);
};
