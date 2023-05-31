#include "MainIsland.hpp"
#include <sys/types.h>

/* ----- Draw ----- */
void MainIsland::drawIsland(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix)
{
    glm::mat4 T = translate(glm::mat4(1), glm::vec3(0, 0, 0));
    T           = translate(T, this->getCenter());

    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uTexture", 0);
    this->_objrenderer.draw();
}
