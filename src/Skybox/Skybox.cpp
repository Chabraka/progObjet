#include "Skybox.hpp"
#include <sys/types.h>
#include <cstdlib>

/* ----- Draw ----- */
void Skybox::drawSkybox(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao, GLuint texture)
{
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, -2));
    T           = glm::translate(T, glm::vec3(_center.x / 2, _center.y, _center.z));

    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uTexture", 0);

    drawOpenGLSkybox(vao, texture);
}