#include "TrackballCamera.hpp"

TrackballCamera::TrackballCamera(float distance, float angleX, float angleY)
    : m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY) {}

void TrackballCamera::moveFront(float delta)
{
    m_fDistance += delta;
}

void TrackballCamera::rotateLeft(float degrees)
{
    m_fAngleY += degrees;
}

void TrackballCamera::rotateUp(float degrees)
{
    m_fAngleX += degrees;
}

glm::mat4 TrackballCamera::getViewMatrix(const Walker& walker) const
{
    glm::mat4 viewMatrix(1.f);
    glm::vec3 translation = -walker.getCenter();

    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.f, 0.f, -m_fDistance));
    viewMatrix = glm::rotate(viewMatrix, m_fAngleX, glm::vec3(1.f, 0.f, 0.f));
    viewMatrix = glm::rotate(viewMatrix, m_fAngleY, glm::vec3(0.f, 1.f, 0.f));
    viewMatrix = glm::translate(viewMatrix, translation);
    return viewMatrix;
}

void TrackballCamera::updatePosition(const glm::vec3& walkerPosition, float orientation)
{
    m_fAngleY            = m_fAngleY * 0.9 + orientation * 0.1;
    const float border   = Parameters::get().BOX_SIZE;
    glm::vec3   position = walkerPosition + glm::vec3(0., 0., m_fDistance);
    if (abs(position.x) < border && abs(position.y) < border && abs(position.z) < border)
    {
        m_position = position;
    }
}
void cameraControls(const p6::Context& ctx, TrackballCamera& camera)
{
    // Rotate
    if (ctx.mouse_button_is_pressed(p6::Button::Left))
    {
        camera.rotateUp(-ctx.mouse_delta().y);
        camera.rotateLeft(ctx.mouse_delta().x);
    }
}