#include "Islands.hpp"

/* ----- Constructor ----- */
Islands::Islands(const uint islandNb, const float border, 
float floor_low_medium, float floor_medium_high, const p6::Shader* shader)
{
    this->renderer = MultiResObjRenderer("assets/models/floating_island_low.obj", 
    "assets/models/floating_island_medium.obj", "assets/models/floating_island.obj", 
        "assets/textures/floating_island.png", shader, 
        floor_low_medium, floor_medium_high);

    for (uint i = 0; i < islandNb; i++)
    {
        Island island(
            glm::vec3(p6::random::number(-(border - 0.1f), border - 0.1f), p6::random::number(-(border - 0.01f), border - 0.1f), p6::random::number(-(border - 0.1f), border - 0.1f))
        );
        _islands.push_back(island);
    }
}

/* ----- Draw ----- */
void Islands::drawIslands(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, glm::vec3 cam_position)
{
    for (uint j = 0; j < _islands.size(); j++)
    {
        float cam_distance = glm::distance(_islands[j].getCenter(), cam_position);
        // std::cout << cam_distance <<"=cam_distance" << std::endl;
        this->drawIsland(&_islands[j],ProjMatrix, ViewMatrix, cam_distance);
    }
}

void Islands::drawIsland(Island *island, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, float cam_distance)
{
    
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
    T           = glm::translate(T, glm::vec3(island->getCenter()));
    // Orientation de l'island:
    // glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), -boid->_speed));
    // float angle = glm::acos(glm::dot(glm::vec3(0.0f, 0.0f, -1.0f), -boid->_speed));    
    T           = glm::rotate(T, glm::radians(island->_angle), glm::vec3(0.0, 1.0, 0.0));

    this->renderer.low_renderer.shader->set("uMVMatrix", T);
    this->renderer.low_renderer.shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    this->renderer.low_renderer.shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    this->renderer.low_renderer.shader->set("uColor", glm::vec3(0.5, 0.8, 0.2));

    this->renderer.draw(cam_distance);
}
