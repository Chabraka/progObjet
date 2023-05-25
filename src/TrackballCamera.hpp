#pragma once

#include "Walker/Walker.hpp"
#include "p6/p6.h"

class TrackballCamera {
private:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

public:
    TrackballCamera(float m_fDistance = 0.5f, float m_fAngleX = 0.f, float m_fAngleY = 0.f);

    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

    glm::mat4 getViewMatrix(/* const Walker& walker */) const;
};

void cameraControls(const p6::Context& ctx, TrackballCamera& camera);