#pragma once

#include "Walker/Walker.hpp"
#include "p6/p6.h"

class TrackballCamera {
private:
    glm::vec3 m_position;
    float     m_fDistance;
    float     m_fAngleX;
    float     m_fAngleY;

public:
    TrackballCamera(float m_fDistance = 0.2f, float m_fAngleX = 0.f, float m_fAngleY = 0.f);

    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void updatePosition(const glm::vec3& walkerPosition) { m_position = walkerPosition + glm::vec3(0., 0., m_fDistance); };

    glm::mat4 getViewMatrix() const;
};

void cameraControls(const p6::Context& ctx, TrackballCamera& camera);