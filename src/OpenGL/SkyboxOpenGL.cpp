#include "SkyboxOpenGL.hpp"
#include <vector>

glm::mat4 translate(float tx, float ty, float tz)
{
    return glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(tx, ty, tz, 1));
}

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
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.335), glm::vec3(0, 0, 1)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.664), glm::vec3(0, 0, 1)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.335), glm::vec3(0, 0, 1)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.664), glm::vec3(0, 0, 1)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.664), glm::vec3(0, 0, 1)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.335), glm::vec3(0, 0, 1)),
        // Left
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.335), glm::vec3(1, 0, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.664), glm::vec3(1, 0, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.001, 0.664), glm::vec3(1, 0, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.001, 0.664), glm::vec3(1, 0, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.001, 0.335), glm::vec3(1, 0, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.335), glm::vec3(1, 0, 0)),
        // Front
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.999, 0.335), glm::vec3(0, 0, -1)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.999, 0.664), glm::vec3(0, 0, -1)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.335), glm::vec3(0, 0, -1)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.664), glm::vec3(0, 0, -1)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.999, 0.664), glm::vec3(0, 0, -1)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.335), glm::vec3(0, 0, -1)),
        // Right
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.335), glm::vec3(-1, 0, 0)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.664), glm::vec3(-1, 0, 0)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.664), glm::vec3(-1, 0, 0)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.664), glm::vec3(-1, 0, 0)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.745, 0.335), glm::vec3(-1, 0, 0)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.335), glm::vec3(-1, 0, 0)),
        // Top
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0.664), glm::vec3(0, -1, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.664), glm::vec3(0, -1, 0)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.499, 0.999), glm::vec3(0, -1, 0)),
        Vertex3DUV(glm::vec3(skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.499, 0.999), glm::vec3(0, -1, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, -skyboxRadius), glm::vec2(0.251, 0.664), glm::vec3(0, -1, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, skyboxRadius, skyboxRadius), glm::vec2(0.251, 0.999), glm::vec3(0, -1, 0)),
        // Floor
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.499, 0), glm::vec3(0, 1, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.25, 0), glm::vec3(0, 1, 0)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.499, 0.335), glm::vec3(0, 1, 0)),
        Vertex3DUV(glm::vec3(skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.499, 0.335), glm::vec3(0, 1, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, -skyboxRadius), glm::vec2(0.25, 0), glm::vec3(0, 1, 0)),
        Vertex3DUV(glm::vec3(-skyboxRadius, -skyboxRadius, skyboxRadius), glm::vec2(0.25, 0.335), glm::vec3(0, 1, 0))};

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

/* --- Textures --- */

GLuint initTex(const img::Image& image)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDisable(GL_BLEND); // Do not blend colors

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (const int&)image.width(), (const int&)image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)(image.data()));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

/* --- Draw --- */

void drawOpenGLSkybox(GLuint vao, GLuint texture)
{
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
