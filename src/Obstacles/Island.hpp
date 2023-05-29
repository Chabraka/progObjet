#pragma once

#include <cstdlib>
#include "../OpenGL/OpenGL.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Island {
    /* Attributes */

public:
    float _angle;

private:
    const float _radius;
    glm::vec3   _center;

    /* Methods */
public:
    // Constructors
    Island()
        : _radius(0.7f), _center(glm::vec3(0.0f)){
            _angle = p6::random::number(0.0, 360.);
        };
    Island(glm::vec3 center)
        : _radius(0.1f), _center(center){
            _angle = p6::random::number(0.0, 360.);
        };

    // Getter
    const glm::vec3 getCenter() const { return _center; };
    const float     getRadius() const { return _radius; };

    // Draw
    void drawIsland(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao);
};