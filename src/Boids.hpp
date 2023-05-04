#pragma once

#include <cstdlib>
#include <vector>
#include "Parameters.hpp"
#include "Square.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boids {
    /* Attributes */
public:
    std::vector<Square> _boids;

    /* Methods */
public:
    // Constructors
    Boids() = default;
    Boids(Parameters& params);

    // Draw
    void drawBoids(p6::Context& ctx, Parameters& params);

    // Update
    void updateBoidsAcc(Square* trackSquare, Parameters& params);
};
