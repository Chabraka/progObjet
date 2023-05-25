#include "glm/ext/matrix_transform.hpp"
#define GLM_FORCE_RADIANS

#include "TrackballCamera.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/trigonometric.hpp"

TrackballCamera::TrackballCamera(float Distance, float AngleX, float AngleY)
    : m_fDistance(Distance), m_fAngleX(AngleX), m_fAngleY(AngleY) {}

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

glm::mat4 TrackballCamera::getViewMatrix(/* const Walker& walker */) const
{
    glm::mat4 viewMatrix(1.f);
    viewMatrix =
        glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -m_fDistance));
    viewMatrix = glm::rotate(viewMatrix, m_fAngleX, glm::vec3(1.f, 0.f, 0.f));
    viewMatrix = glm::rotate(viewMatrix, m_fAngleY, glm::vec3(0.f, 1.f, 0.f));
    return viewMatrix;
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
