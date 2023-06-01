#include "MainIsland.hpp"
#include <sys/types.h>

/* ----- Draw ----- */
void MainIsland::drawIsland(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix,  Light sun, Light walker)
{
    glm::mat4 T = translate(glm::mat4(1), glm::vec3(0, 0, 0));
    T           = translate(T, glm::vec3(this->_center.x / 2, this->_center.y, this->_center.z));

    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uTexture", 0);

	shader->set("uKd", this->lightProp.diffuse);
    shader->set("uKs", this->lightProp.specular);
    shader->set("uShininess", this->lightProp.shininess);


	shader->set("uSunPosition", sun.position);
    shader->set("uSunIntensity", sun.intensity);
	shader->set("uWalkerPosition", walker.position);
    shader->set("uWalkerIntensity", walker.intensity);

    this->_objrenderer.draw();

    ;
}
