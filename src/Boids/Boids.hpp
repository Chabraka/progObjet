#pragma once

#include <cstdlib>
#include <vector>
#include "../Light.hpp"
#include "../Obstacles/Island.hpp"
#include "../Obstacles/MainIsland.hpp"
#include "../Parameters.hpp"
#include "Boid.hpp"
#include "OpenGL/ObjRenderer.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "p6/p6.h"

class Boids {
    /* Attributes */
public:
    std::vector<Boid>   _boids;
    MultiResObjRenderer renderer;
    LightProperties     light;

    /* Methods */
public:
    // Constructors
    Boids() = default;
    Boids(const p6::Shader* shader);
    Boids(const p6::Shader* shader, const LightProperties& light);

    // Draw
    void drawBoid(Boid* boid, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, float cam_distance, Light sun, Light walker);
    void drawBoids(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, float dt, const glm::vec3& cam_position, const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland, Light sun, Light walker);

    // Update
    void updateBoidsAcc();
};

// ImGui
void boidsImGui();