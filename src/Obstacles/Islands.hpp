#pragma once

#include <sys/types.h>
#include <cstdlib>
#include <vector>
#include "../OpenGL/ObjRenderer.hpp"
#include "../Parameters.hpp"
#include "Island.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Islands {
    /* Attributes */
public:
    std::vector<Island> _islands;
    MultiResObjRenderer renderer;
    LightProperties     light;

    /* Methods */
public:
    // Constructors
    Islands()                     = delete;
    Islands(const Island& island) = delete;
    Islands(const uint islandNb, const p6::Shader* shader);
    Islands(const uint islandNb, const p6::Shader* shader, LightProperties lightprop);

    // Draw
    void drawIsland(Island* island, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, const float& cam_distance, Light sun, Light walker);
    void drawIslands(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, glm::vec3 cam_position, Light sun, Light walker);
};
