#pragma once

#include "glm/glm.hpp"

typedef struct LightProperties {
    glm::vec3 diffuse;
    glm::vec3 specular;
    float     shininess;

    LightProperties(const glm::vec3& diff, const glm::vec3& spec, float shin)
        : diffuse(diff), specular(spec), shininess(shin)
    {}

    // Constructeur par défaut
    LightProperties()
        : diffuse(glm::vec3(0.0f)), specular(glm::vec3(0.0f)), shininess(0.0f)
    {}

} LightProperties;

typedef struct Light {
    glm::vec3 position;
    glm::vec3 intensity;

    Light(const glm::vec3& pos, const glm::vec3& inten)
        : position(pos), intensity(inten)
    {}

} Light;