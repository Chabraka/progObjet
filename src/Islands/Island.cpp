#include "Island.hpp"
#include <sys/types.h>

/* ----- Draw ----- */
void Island::drawIsland(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao)
{
    glm::mat4 T = translate(glm::mat4(1), glm::vec3(0, 0, 0));
    T           = translate(T, glm::vec3(this->_center.x / 2, this->_center.y, this->_center.z));

    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uColor", glm::vec3(0.9, 0.2, 0.1));

    drawOpenGL(vao);
}
