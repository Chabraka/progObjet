#pragma once

#include "glm/ext/matrix_transform.hpp"
#define GLM_FORCE_RADIANS

#include "Walker/Walker.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/trigonometric.hpp"
#include "p6/p6.h"

class TrackballCamera {
private:
    glm::vec3 m_position;

public:
    float m_fDistance;

private:
    float m_fAngleX;
    float m_fAngleY;

public:
    TrackballCamera(float m_fDistance = 0.5f, float m_fAngleX = 0.f, float m_fAngleY = 0.f);

    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void updatePosition(const glm::vec3& walkerPosition, float orientation);

    glm::mat4 getViewMatrix(const Walker& walker) const;
};

void cameraControls(const p6::Context& ctx, TrackballCamera& camera);