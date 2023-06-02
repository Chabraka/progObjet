#include "Islands.hpp"

/* ----- Constructor ----- */
Islands::Islands(const uint islandNb, const p6::Shader* shader, LightProperties lightprop)
    : Islands(islandNb, shader)
{
    light = lightprop;
}

Islands::Islands(const uint islandNb, const p6::Shader* shader)
{
    this->renderer     = MultiResObjRenderer("assets/models/floating_island_low.obj", "assets/models/floating_island_medium.obj", "assets/models/floating_island.obj", "assets/textures/floating_island.png", shader, Parameters::get().FLOOR_LOW_MEDIUM, Parameters::get().FLOOR_MEDIUM_HIGH);
    const float border = Parameters::get().BOX_SIZE;
    for (uint i = 0; i < islandNb; i++)
    {
        Island island(
            glm::vec3(p6::random::number(-(border - 0.1f), border - 0.1f), p6::random::number(-(border - 0.1f), border - 0.1f), p6::random::number(-(border - 0.1f), border - 0.1f))
        );
        _islands.push_back(island);
    }
}

/* ----- Draw ----- */

void Islands::drawIsland(Island* island, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, const float& cam_distance, Light sun, Light walker)
{
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
    T           = glm::translate(T, glm::vec3(island->getCenter()));

    // Island's orientation
    T = glm::rotate(T, glm::radians(island->_angle), glm::vec3(0.0, 1.0, 0.0));

    this->renderer.low_renderer.shader->use();
    this->renderer.low_renderer.shader->set("uMVMatrix", T);
    this->renderer.low_renderer.shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    this->renderer.low_renderer.shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    this->renderer.low_renderer.shader->set("uColor", glm::vec3(0.5, 0.8, 0.2));
    this->renderer.low_renderer.shader->set("uKd", this->light.diffuse);
    this->renderer.low_renderer.shader->set("uKs", this->light.specular);
    this->renderer.low_renderer.shader->set("uShininess", this->light.shininess);
    this->renderer.low_renderer.shader->set("uSunPosition", sun.position);
    this->renderer.low_renderer.shader->set("uSunIntensity", sun.intensity);
    this->renderer.low_renderer.shader->set("uWalkerPosition", walker.position);
    this->renderer.low_renderer.shader->set("uWalkerIntensity", walker.intensity);

    this->renderer.draw(cam_distance);
}

void Islands::drawIslands(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, glm::vec3 cam_position, Light sun, Light walker)
{
    for (uint j = 0; j < _islands.size(); j++)
    {
        float cam_distance = glm::distance(_islands[j].getCenter(), cam_position);
        this->drawIsland(&_islands[j], ProjMatrix, ViewMatrix, cam_distance, sun, walker);
    }
}