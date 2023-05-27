#pragma once

#include <sys/types.h>
#include <cstdlib>
#include <vector>
#include "Island.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Islands {
    /* Attributes */
public:
    std::vector<Island> _islands;

    /* Methods */
public:
    // Constructors
    Islands()                     = delete;
    Islands(const Island& island) = delete;
    Islands(const uint islandNb, const float border); // Only constructor available

    // Draw
    void drawIslands(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao);
};
