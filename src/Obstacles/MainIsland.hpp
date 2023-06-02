#pragma once

#include <sys/types.h>
#include <cstdlib>
#include "../Light/Light.hpp"
#include "../OpenGL/ObjRenderer.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class MainIsland {
    /* Attributes */

private:
    const float     _radius;
    glm::vec3       _center;
    ObjRenderer     _objrenderer;
    LightProperties lightProp;

    /* Methods */
public:
    // Constructors
    MainIsland(const p6::Shader* shader)
        : _radius(0.7f), _center(glm::vec3(0.0f)), _objrenderer(ObjRenderer("assets/models/main_island_light.obj", "assets/textures/floating_island.png", shader)), lightProp(LightProperties(glm::vec3(1), glm::vec3(0), 0.f)){};
    MainIsland(glm::vec3 center, const p6::Shader* shader)
        : _radius(0.1f), _center(center), _objrenderer(ObjRenderer("assets/models/main_island_light.obj", "assets/textures/floating_island.png", shader)), lightProp(LightProperties(glm::vec3(1), glm::vec3(0), 0.f)){};

    // Getter
    glm::vec3 getCenter() const { return _center; };
    float     getRadius() const { return _radius; };

    // Draw
    void drawIsland(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, Light sun, Light walker);
};