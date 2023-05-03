#pragma once

#include <cstdlib>
#include <vector>
#include "Parameters.hpp"
#include "Square.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boids {
    // private:
public:
    std::vector<Square> _boids;

public:
    // Boids(int squareNumber, int maxSquareNumber, float minSpeed, float maxSpeed, float minDistance, float factorAttraction, float factorRepulsion, float maxRepulsion, float factorAttractTracker);
    Boids() = default;
    Boids(Parameters& params);

    // Drawing
    void drawBoids(p6::Context& ctx, Parameters& params);

    // Updates
    void updateBoidsAcc(Square* trackSquare, Parameters& params);
};
