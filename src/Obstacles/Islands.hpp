#pragma once

#include <sys/types.h>
#include <cstdlib>
#include <vector>
#include "Island.hpp"
#include "../Light.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "OpenGL/ObjRenderer.hpp"

class Islands {
    /* Attributes */
public:
    std::vector<Island> _islands;
    MultiResObjRenderer renderer;
	LightProperties light;

    /* Methods */
public:
    // Constructors
    Islands()                     = delete;
    Islands(const Island& island) = delete;
    Islands(const uint islandNb,
            const float border, float floor_low_medium, float floor_medium_high,
            const p6::Shader* shader); // Only constructor available
	Islands(const uint islandNb,
            const float border, float floor_low_medium, float floor_medium_high,
            const p6::Shader* shader, LightProperties lightprop);

    // Draw
    void drawIslands(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix,
                     glm::vec3 cam_position, Light sun, Light walker);
    void drawIsland(Island *island, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix,
    float cam_distance, Light sun, Light walker);
};
