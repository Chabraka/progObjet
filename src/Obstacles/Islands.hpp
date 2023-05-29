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
    MultiResObjRenderer renderer;

    /* Methods */
public:
    // Constructors
    Islands()                     = delete;
    Islands(const Island& island) = delete;
    Islands(const uint islandNb, 
            const float border, float floor_low_medium, float floor_medium_high, 
            const p6::Shader* shader); // Only constructor available

    // Draw
    void drawIslands(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, 
                     glm::vec3 cam_position);
    void drawIsland(Island *island, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, 
    float cam_distance);
};
