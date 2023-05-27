#pragma once

#include <cstddef>
#include <cstdlib>
#include <vector>
#include "../Skybox/Skybox.hpp"
#include "ObjLoader.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "img/src/Image.h"
#include "p6/p6.h"

glm::mat4 translate(float tx, float ty, float tz);

struct Vertex3DColor {
    glm::vec3 _position;
    glm::vec3 _color;

    Vertex3DColor() = default;
    Vertex3DColor(glm::vec3 p, glm::vec3 c)
        : _position(p), _color(c){};
};

struct Vertex3DUV {
    glm::vec3 _position;
    glm::vec2 _coordTex;

    Vertex3DUV() = default;
    Vertex3DUV(glm::vec3 p, glm::vec2 c)
        : _position(p), _coordTex(c){};
};

struct MatrixView {
    glm::mat4 _ProjMatrix;
    glm::mat4 _MMatrix;
    glm::mat4 _MVPMatrix;
    glm::mat4 _NormalMatrix;

    MatrixView()
        : _ProjMatrix(glm::perspective(glm::radians(70.f), 1.77f, 0.1f, 100.f)), _MMatrix(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -2.f))), _NormalMatrix(glm::transpose(glm::inverse(_MMatrix))){};

    void setMatrix();
};

class ObjRenderer {
    /* Attributes */

public:
    GLuint      vao;
    int         vertex_size;
    p6::Shader* shader;
    GLuint      texture;

    /* Methods */
public:
    // Constructors
    ObjRenderer(const char* obj_path, const char* image_path, const p6::Shader* shader);

    // Draw
    void draw(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix);
};

GLuint initOpenGLSkybox(const float& skyboxRadius);
GLuint initOpenGLWalker();
GLuint initOpenGLTracker();
GLuint initOpenGLBoids();
GLuint initOpenGLMainIsland();
GLuint initOpenGLIslands();
GLuint initOpenGLModel();
GLuint initTex(const img::Image& image);

void drawOpenGL(GLuint vao);
void drawOpenGLModel(GLuint vao, GLuint texture, int size);
void drawOpenGLSkybox(GLuint vao, GLuint texture);
void drawOpenGLBoids(GLuint vao);