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

private:
    uint _islandNb;

    /* Methods */
public:
    // Constructors
    Islands() = default;
    Islands(const uint islandNb);

    // Draw
    void drawIslands(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao);
};
