#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "glm/gtx/transform.hpp"
#include "glm/fwd.hpp"


class FreeflyCamera {

private:

    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

public:
    FreeflyCamera() : m_Position(0,0,5), m_fPhi(glm::pi<float>()), m_fTheta(0) {
        computeDirectionVectors();
    }

    void computeDirectionVectors();

    void moveLeft(float t);
    void moveFront(float t);

    void rotateLeft(float degrees);
    void rotateUp(float degrees);


    void setPos(glm::vec3 position);
    void setPhi(float degrees);
    void setTheta(float degrees);

    glm::mat4 getViewMatrix() const;
};
