#include <cstdlib>
#include "OpenGL/ObjRenderer.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Model {
    /* Attributes */

private:
    const glm::float32 _radius;
    glm::vec3          _center;
    glm::vec3          _speed;
    glm::vec3          _acceleration;
    ObjRenderer        _objrenderer;

    // Gluint vao;

    /* Methods */
public:
    // Constructors
    Model(const char* obj_path, const char* image_path, const p6::Shader* shader)
        : _radius(1.0f), _center(glm::vec3(0.0f)), _speed(glm::vec3(1.0f)), _acceleration(glm::vec3(1.0f)), _objrenderer(ObjRenderer(obj_path, image_path, shader)){};
    Model(const char* obj_path, const char* image_path, const p6::Shader* shader, glm::float32 radius, glm::vec3 center, glm::vec3 speed, glm::vec3 acceleration)
        : _radius(radius), _center(center), _speed(speed), _acceleration(acceleration), _objrenderer(ObjRenderer(obj_path, image_path, shader)){};

    // Draw
    void drawModel(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix);

    // Update
    void updatePosition(float minSpeed, float maxSpeed);
};