#define GLM_FORCE_RADIANS

#include "Camera.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"



void FreeflyCamera::computeDirectionVectors()
{
    m_FrontVector = glm::vec3(glm::cos(m_fTheta) * glm::sin(m_fPhi), glm::sin(m_fTheta), glm::cos(m_fTheta) * glm::cos(m_fPhi));

    m_LeftVector = glm::vec3(glm::sin(m_fPhi + (glm::pi<float>()/2.f)), 0, glm::cos(m_fPhi + (glm::pi<float>() / 2.f)));

    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

void FreeflyCamera::moveLeft(float t)
{
    m_Position += t * m_LeftVector;
}

void FreeflyCamera::moveFront(float t)
{
    m_Position += t * m_FrontVector;
}

void FreeflyCamera::rotateLeft(float degrees)
{
    m_fPhi += glm::radians(degrees);
    computeDirectionVectors();
}

void FreeflyCamera::rotateUp(float degrees)
{
    m_fTheta += glm::radians(degrees);
    computeDirectionVectors();
}


void FreeflyCamera::setPos(glm::vec3 position)
{
    m_Position = position;
}

void FreeflyCamera::setPhi(float degrees)
{
    m_fPhi = glm::radians(degrees);
    computeDirectionVectors();
}

void FreeflyCamera::setTheta(float degrees)
{
    m_fTheta = glm::radians(degrees);
    computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const
{
    return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}
