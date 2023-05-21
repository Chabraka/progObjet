#pragma once

#include <glm/glm.hpp>


class TrackballCamera {

private:

    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

public:

    TrackballCamera(float m_fDistance=5.f, float m_fAngleX=0.f, float m_fAngleY=0.f);
    
    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void dump();
    glm::mat4 getViewMatrix() const;

};

