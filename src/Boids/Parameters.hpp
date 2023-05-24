#pragma once

#include <cstdlib>
#include <vector>
#include "glm/fwd.hpp"
#include "p6/p6.h"

struct Parameters {
public:
    int   BOID_NB                = 100;
    int   MAX_BOID_NB            = 200;
    float MIN_SPEED              = 0.01f;
    float MAX_SPEED              = 0.5f;
    float MIN_DIST               = 0.7f;
    float FACTOR_ATTRACTION      = 0.001f;
    float FACTOR_REPULSION       = -0.02f;
    float MAX_REPULSION          = -3.f;
    float FACTOR_ATTRACT_TRACKER = 0.15f;

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