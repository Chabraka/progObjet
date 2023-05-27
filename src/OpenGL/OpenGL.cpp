#include "OpenGL.hpp"
#include <vector>
#include "Loader/Loader.hpp"
#include "ObjLoader.hpp"



 ObjRenderer::ObjRenderer(const char* obj_path, const char* image_path, const p6::Shader* shader){
    std::vector<glimac::ShapeVertex> vertices=LoadOBJ(obj_path);
    this->vao = 1;
    this->vertex_size = 1;
    this->shader=nullptr;
    this->texture=1;
 }
   
glm::mat4 translate(float tx, float ty, float tz)
{
    return glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(tx, ty, tz, 1));
}


/* --- ObjRendere */


/* --- Init --- */

GLuint initOpenGLSkybox(const float& skyboxRadius)
{
    /* --- VBO --- */
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //  Tab with coordinates
    Vertex3DUV skybox[] = {
        // Back
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.335)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.664)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.335)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.664)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.664)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.335)),
        // Left
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.335)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.664)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.001, 0.664)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.001, 0.664)),
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.001, 0.335)),
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.335)),
        // Front
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.999, 0.335)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.999, 0.664)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.335)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.664)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.999, 0.664)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.335)),
        // Right
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.335)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.664)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.664)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.664)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.335)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.335)),
        // Top
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.664)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.664)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.499, 0.999)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.499, 0.999)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.664)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.251, 0.999)),
        // Floor
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.25, 0)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.499, 0.335)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.499, 0.335)),
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.25, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.25, 0.335)),

    };

    glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(Vertex3DUV), skybox, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* --- VAO --- */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_TEXTURE  = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

    /* --- Binding --- */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV), (const GLvoid*)(offsetof(Vertex3DUV, _position)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV), (const GLvoid*)(offsetof(Vertex3DUV, _coordTex)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

GLuint initOpenGLWalker(const float& walkerRadius)
{
    /* --- VBO --- */
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //  Tab with coordinates
    Vertex3DColor tracker[] = {
        Vertex3DColor(glm::vec3(-walkerRadius, -walkerRadius, -walkerRadius), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-walkerRadius, walkerRadius, -walkerRadius), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(walkerRadius, -walkerRadius, -walkerRadius), glm::vec3(0, 0, 1)),
        Vertex3DColor(glm::vec3(walkerRadius, walkerRadius, -walkerRadius), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-walkerRadius, walkerRadius, -walkerRadius), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(walkerRadius, -walkerRadius, -walkerRadius), glm::vec3(0, 0, 1)),
    };

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex3DColor), tracker, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* --- VAO --- */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR    = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    /* --- Binding --- */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

GLuint initOpenGLTracker()
{
    /* --- VBO --- */
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //  Tab with coordinates
    Vertex3DColor tracker[] = {
        Vertex3DColor(glm::vec3(-0.05, -0.05, -0.05), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-0.05, 0.05, -0.05), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(0.05, -0.05, -0.05), glm::vec3(0, 0, 1)),
        Vertex3DColor(glm::vec3(0.05, 0.05, -0.05), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-0.05, 0.05, -0.05), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(0.05, -0.05, -0.05), glm::vec3(0, 0, 1)),
    };

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex3DColor), tracker, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* --- VAO --- */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR    = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    /* --- Binding --- */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

GLuint initOpenGLBoids()
{
    /* --- VBO --- */
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    Vertex3DColor boids[] = {
        Vertex3DColor(glm::vec3(0., 0.01, 0.08), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(-0.05, 0., 0.), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(-0.02, 0.01, 0.), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(0., 0.01, 0.08), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(-0.02, 0.01, 0.), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(0., -0.02, 0.), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(0., 0.01, 0.08), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(0., -0.02, 0.), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(0.02, 0.01, 0.), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(0., 0.01, 0.08), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(0.02, 0.01, 0.), glm::vec3(0.5)),
        Vertex3DColor(glm::vec3(0.05, 0., 0.), glm::vec3(0.5))};

    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(Vertex3DColor), boids, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* --- VAO --- */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR    = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    /* --- Binding --- */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

GLuint initOpenGLMainIsland()
{
    /* --- VBO --- */
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //  Tab with coordinates
    Vertex3DColor mainIsland[] = {
        Vertex3DColor(glm::vec3(-0.5, 0., -0.5), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-0.5, 0., 0.5), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(0.5, 0., -0.5), glm::vec3(0, 0, 1)),
        Vertex3DColor(glm::vec3(0.5, 0., 0.5), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-0.5, 0., 0.5), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(0.5, 0., -0.5), glm::vec3(0, 0, 1)),
    };

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex3DColor), mainIsland, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* --- VAO --- */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR    = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    /* --- Binding --- */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

GLuint initOpenGLIslands()
{
    /* --- VBO --- */
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //  Tab with coordinates
    Vertex3DColor mainIsland[] = {
        Vertex3DColor(glm::vec3(-0.05, 0., -0.05), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-0.05, 0., 0.05), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(0.05, 0., -0.05), glm::vec3(0, 0, 1)),
        Vertex3DColor(glm::vec3(0.05, 0., 0.05), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-0.05, 0., 0.05), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(0.05, 0., -0.05), glm::vec3(0, 0, 1)),
    };

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex3DColor), mainIsland, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* --- VAO --- */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR    = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    /* --- Binding --- */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

GLuint initOpenGLModel()
{

    // via ObjLoader
    const char * filename= "assets/models/monkey.obj";
    std::vector<glimac::ShapeVertex> shapevertexes = LoadOBJ(filename);
    std::cout << "shapevertexes" << " " << shapevertexes.size() << std::endl;

    std::vector<Vertex3DUV> vv;
    for (int i=0; i < shapevertexes.size(); i++){
        vv.push_back(Vertex3DUV(shapevertexes[i].position, shapevertexes[i].texCoords));
    };

    

    /* --- VBO --- */
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::cout << vv.size() << std::endl;
    //glBufferData(GL_ARRAY_BUFFER, shapevertexes.size() * sizeof(glimac::ShapeVertex), &shapevertexes, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, shapevertexes.size() * sizeof(Vertex3DColor), vvtab, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, vv.size()  * sizeof(Vertex3DColor), vvtab, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, 12  * sizeof(Vertex3DColor), &vv, GL_STATIC_DRAW);


    //glBufferData(GL_ARRAY_BUFFER, shapevertexes.size() * sizeof(Vertex3DUV), vvtab, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vv.size() * sizeof(Vertex3DUV), &vv[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* --- VAO --- */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR    = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    // glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    glDisableVertexAttribArray(VERTEX_ATTR_COLOR);
    // glDisableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

    /* --- Binding --- */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV), (const GLvoid*)(offsetof(Vertex3DUV, _position)));
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _color)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV), (const GLvoid*)(offsetof(Vertex3DUV, _coordTex)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

/* --- Textures --- */

GLuint initTex(const img::Image& image)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDisable(GL_BLEND);  // Éviter le mélange dés couleurs ???

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (const int&)image.width(), (const int&)image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)(image.data()));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}



/* --- Draw --- */

void drawOpenGL(GLuint vao)
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void drawOpenGLSkybox(GLuint vao, GLuint texture)
{
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);

}

void drawOpenGLBoids(GLuint vao)
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glBindVertexArray(0);
}

void drawOpenGLModel(GLuint vao, GLuint texture, int size)
{
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, size);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}