#include "Islands.hpp"

/* ----- Constructor ----- */
Islands::Islands(const uint islandNb, const float border)
{
    for (uint i = 0; i < islandNb; i++)
    {
        Island island(
            glm::vec3(p6::random::number(-(border - 0.1f), border - 0.1f), p6::random::number(-(border - 0.01f), border - 0.1f), p6::random::number(-(border - 0.1f), border - 0.1f))
        );
        _islands.push_back(island);
    }
}

/* ----- Draw ----- */
void Islands::drawIslands(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao)
{
    for (uint j = 0; j < _islands.size(); j++)
    {
        _islands[j].drawIsland(shader, ProjMatrix, ViewMatrix, vao);
    }
}
