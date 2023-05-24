#include "Islands.hpp"

/* ----- Constructor ----- */
Islands::Islands(const uint islandNb)
{
    _islandNb = islandNb;
    for (uint i = 0; i < _islandNb; i++)
    {
        Island island(
            glm::vec3(p6::random::number(-3.5f, 3.5f), p6::random::number(-3.5f, 3.5f), p6::random::number(-3.5f, 3.5f))
        );
        _islands.push_back(island);
    }
}

/* ----- Draw ----- */
void Islands::drawIslands(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao)
{
    for (uint j = 0; j < _islandNb; j++)
    {
        _islands[j].drawIsland(shader, ProjMatrix, ViewMatrix, vao);
    }
}
