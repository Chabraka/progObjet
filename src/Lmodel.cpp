

#include "Lmodel.hpp"
#include <sys/types.h>
#include "OpenGL/OpenGL.hpp"

/* ----- Draw ----- */
void Model::drawModel(const p6::Shader* shader, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, GLuint vao)
{
    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, -2));
    T           = glm::translate(T, glm::vec3(this->_center.x / 2, this->_center.y, this->_center.z));

    shader->set("uMVMatrix", T);
    shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    shader->set("uColor", glm::vec3(0.5, 0.8, 0.2));

    drawOpenGL(vao);
}

/* ----- Restrictions ----- */


/* ----- Behaviors ----- */



/* ----- Updates ----- */

// void Model::updatePosition(float minSpeed, float maxSpeed)
// {
//     float dt = 1.0 / 60.;

//     // Calcul of the position
//     this->_center.x += this->_speed.x * dt + this->_acceleration.x * dt * dt / 2;
//     this->_center.y += this->_speed.y * dt + this->_acceleration.y * dt * dt / 2;
//     this->_center.z += this->_speed.z * dt + this->_acceleration.z * dt * dt / 2;

//     // Calcul of the speed
//     this->_speed.x += this->_acceleration.x * dt;
//     this->_speed.y += this->_acceleration.y * dt;
//     this->_speed.z += this->_acceleration.z * dt;

//     // Restrict the position
// }




// std::vector<glm::vec3> vertices;
//     std::vector<glm::vec3> texv;
//     std::vector<glm::vec3> normalv;

//     readVertices("../assets/models/cube.obj", vertices, texv,normalv );

//     GLuint vbo;
//     glGenBuffers(1, &vbo);

//     glBindBuffer(GL_ARRAY_BUFFER, vbo);

//     glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glimac::ShapeVertex), &vertices, GL_STATIC_DRAW);

//     glBindBuffer(GL_ARRAY_BUFFER, 0);

//     GLuint vao;
//     glGenVertexArrays(1, &vao);

//     glBindVertexArray(vao);

//     glEnableVertexAttribArray(0);
//     glEnableVertexAttribArray(1);
//     glEnableVertexAttribArray(2);


//     glBindBuffer(GL_ARRAY_BUFFER, vbo);

//     GLint myLoc;
//     GLint myNormal;
//     GLint myCoords;

//     GLint uMVPMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    
//     GLint uMVMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVMatrix");
//     GLint uNormalMatrixLoc =glGetUniformLocation(program.getGLId(), "uNormalMatrix");

//     myLoc = glGetUniformLocation(program.getGLId(), "vPosition_vs");
//     myNormal = glGetUniformLocation(program.getGLId(), "vNormal_s");
//     myCoords= glGetUniformLocation(program.getGLId(), "vPTexCoords_vs");


//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid *)(offsetof(ShapeVertex, position)));
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid *)(offsetof(ShapeVertex, normal)));
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid *)(offsetof(ShapeVertex, texCoords)));

//     glBindBuffer(GL_ARRAY_BUFFER, 0);

//     glBindVertexArray(0);

   

//     glEnable(GL_DEPTH_TEST);
    

//     glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)(800/600), 0.1f,100.f);

//     glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0.,0.,-5.));

//     glm::mat4 NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
