#pragma once

#include <cstdlib>
#include <vector>
#include "glm/fwd.hpp"
#include "p6/p6.h"

struct Parameters {
public:
    int         BOID_NB           = 100;
    const int   MAX_BOID_NB       = 300;
    float       MIN_SPEED         = 0.01f;
    float       MAX_SPEED         = 0.4f;
    float       MIN_DIST          = 0.7f;
    float       FACTOR_ATTRACTION = 0.001f;
    float       FACTOR_REPULSION  = -0.110f;
    float       MAX_REPULSION     = -3.f;
    const float BOX_SIZE          = 3.f;
    float       FLOOR_LOW_MEDIUM  = 3.0;
    float       FLOOR_MEDIUM_HIGH = 0.4;

private:
    Parameters() = default;

public:
    Parameters(Parameters& p) = delete;
    static Parameters& get()
    {
        static Parameters PARAMS;
        return PARAMS;
    }
};
