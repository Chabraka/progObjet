#include <cstdlib>
#include "Tracker/Tracker.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Model {
    /* Attributes */
    
public:
    int _vertex_size;

private:
    const glm::float32 _radius;
    glm::vec3 _center;
    glm::vec3 _speed;
    glm::vec3 _acceleration;

    // Gluint vao;

    /* Methods */
public:
    // Constructors
    Model()
        : _radius(1.0f), _center(glm::vec3(0.0f)), _speed(glm::vec3(1.0f)), _acceleration(glm::vec3(1.0f)),_vertex_size(0){};
    Model(glm::float32 radius, glm::vec3 center, glm::vec3 speed, glm::vec3 acceleration)
        : _radius(radius), _center(center), _speed(speed), _acceleration(acceleration), _vertex_size(0){};

    // Draw
    void drawModel(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao, GLuint texture);

    // Update
    void      updatePosition(float minSpeed, float maxSpeed);

   
};