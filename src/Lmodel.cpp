#include "Lmodel.hpp"
#include <sys/types.h>
#include "OpenGL/OpenGL.hpp"

/* ----- Draw ----- */
void Model::drawModel(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao, GLuint texture)
{
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, -2));
    T           = glm::translate(T, glm::vec3(this->_center.x, this->_center.y, this->_center.z));

    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uTexture", 0);
    // shader->set("uColor", glm::vec3(0.0, 0.5, 0.5));

    drawOpenGLModel(vao, texture, this->_vertex_size);
}

/* ----- Restrictions ----- */

/* ----- Behaviors ----- */

/* ----- Updates ----- */

void Model::updatePosition(float minSpeed, float maxSpeed)
{
    float dt = 1.0 / 60.;

    // Calcul of the position
    this->_center.x += this->_speed.x * dt + this->_acceleration.x * dt * dt / 2;
    this->_center.y += this->_speed.y * dt + this->_acceleration.y * dt * dt / 2;
    this->_center.z += this->_speed.z * dt + this->_acceleration.z * dt * dt / 2;

    // Calcul of the speed
    this->_speed.x += this->_acceleration.x * dt;
    this->_speed.y += this->_acceleration.y * dt;
    this->_speed.z += this->_acceleration.z * dt;

    // Restrict the position
}
