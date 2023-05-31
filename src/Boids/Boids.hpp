#pragma once

#include <cstdlib>
#include <vector>
#include "../Parameters.hpp"
#include "Boid.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "p6/p6.h"
#include "../Light.hpp"

class Boids {
    /* Attributes */
public:
    std::vector<Boid> _boids;
    MultiResObjRenderer renderer;
    Light light;

    /* Methods */
public:
    // Constructors
    Boids() = default;
    Boids(Parameters& params, float floor_low_medium, float floor_medium_high, const p6::Shader* shader);
    Boids(Parameters& params, float floor_low_medium, float floor_medium_high, const p6::Shader* shader, glm::vec3 diffuse, glm::vec3 specular, float shininess);

    // Draw
    void drawBoids(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, Parameters& params, float dt, glm::vec3 cam_position, glm::vec3 lightpos, glm::vec3 lightIntensity);

    void drawBoid(Boid *boid, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, float cam_distance, glm::vec3 lightpos, glm::vec3 lightIntensity);

    // Update
    void updateBoidsAcc(Tracker* tracker, Parameters& params);
};
