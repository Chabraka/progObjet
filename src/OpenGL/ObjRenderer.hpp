#pragma once

#include <cstddef>
#include <cstdlib>
#include <vector>
#include "../Loader/ObjLoader.hpp"
#include "SkyboxOpenGL.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "img/src/Image.h"
#include "p6/p6.h"

class ObjRenderer {
    /* Attributes */
public:
    GLuint            vao;
    int               vertex_size;
    const p6::Shader* shader;
    GLuint            texture;

private:
    void _initGL(const char* obj_path);

    /* Methods */
public:
    // Constructors
    ObjRenderer();
    ObjRenderer(const char* obj_path, const char* image_path, const p6::Shader* shader);
    ObjRenderer(const char* obj_path, GLuint texture, const p6::Shader* shader);

    // Draw
    void draw();
};

class MultiResObjRenderer {
public:
    ObjRenderer low_renderer;
    ObjRenderer medium_renderer;
    ObjRenderer high_renderer;

private:
    float _floor_low_medium;
    float _floor_medium_high;

public:
    MultiResObjRenderer(){};
    MultiResObjRenderer(
        const char* low_obj_path, const char* medium_obj_path, const char* high_obj_path,
        const char* image_path, const p6::Shader* shader
    );

    void draw(float cam_distance);
};