#include "OpenGL.hpp"

glm::mat4 translate(float tx, float ty, float tz)
{
    return glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(tx, ty, tz, 1));
}

/* --- Init --- */

GLuint initOpenGLSkybox()
{
    /* --- VBO --- */
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //  Tab with coordinates
    Vertex3DColor skybox[] = {
        // Back
        Vertex3DColor(glm::vec3(-4, -4, -4), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-4, 4, -4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, -4, -4), glm::vec3(0, 0, 1)),
        Vertex3DColor(glm::vec3(4, 4, -4), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-4, 4, -4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, -4, -4), glm::vec3(0, 0, 1)),
        // Left
        Vertex3DColor(glm::vec3(-4, -4, -4), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-4, 4, -4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(-4, 4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(-4, 4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(-4, -4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(-4, -4, -4), glm::vec3(1, 0, 0)),
        // Front
        Vertex3DColor(glm::vec3(-4, -4, 4), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-4, 4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, -4, 4), glm::vec3(0, 0, 1)),
        Vertex3DColor(glm::vec3(4, 4, 4), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-4, 4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, -4, 4), glm::vec3(0, 0, 1)),
        // Right
        Vertex3DColor(glm::vec3(4, -4, -4), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(4, 4, -4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, 4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, 4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, -4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, -4, -4), glm::vec3(1, 0, 0)),
        // Top
        Vertex3DColor(glm::vec3(4, 4, -4), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-4, 4, -4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, 4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, 4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(-4, 4, -4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(-4, 4, 4), glm::vec3(1, 0, 0)),
        // Back
        Vertex3DColor(glm::vec3(4, -4, -4), glm::vec3(1, 0, 0)),
        Vertex3DColor(glm::vec3(-4, -4, -4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, -4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(4, -4, 4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(-4, -4, -4), glm::vec3(0, 1, 0)),
        Vertex3DColor(glm::vec3(-4, -4, 4), glm::vec3(1, 0, 0)),

    };

    glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(Vertex3DColor), skybox, GL_STATIC_DRAW);
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

    /*
    Vertex3DUV boids[] = {
        Vertex3DUV(glm::vec3(0., 0.01, 0.08), glm::vec2(0.5, 0.5)),
        Vertex3DUV(glm::vec3(-0.05, 0., 0.), glm::vec2(0, 0)),
        Vertex3DUV(glm::vec3(-0.02, 0.01, 0.), glm::vec2(0.3, 0)),
        Vertex3DUV(glm::vec3(0., 0.01, 0.08), glm::vec2(0.5, 0.5)),
        Vertex3DUV(glm::vec3(-0.02, 0.01, 0.), glm::vec2(0.3, 0)),
        Vertex3DUV(glm::vec3(0., -0.02, 0.), glm::vec2(0.5, 0)),
        Vertex3DUV(glm::vec3(0., 0.01, 0.08), glm::vec2(0.5, 0.5)),
        Vertex3DUV(glm::vec3(0., -0.02, 0.), glm::vec2(0.5, 0)),
        Vertex3DUV(glm::vec3(0.02, 0.01, 0.), glm::vec2(0.7, 0)),
        Vertex3DUV(glm::vec3(0., 0.01, 0.08), glm::vec2(0.5, 0.5)),
        Vertex3DUV(glm::vec3(0.02, 0.01, 0.), glm::vec2(0.7, 0)),
        Vertex3DUV(glm::vec3(0.05, 0., 0.), glm::vec2(0, 1))};

    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(Vertex3DUV), boids, GL_STATIC_DRAW); */

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* --- VAO --- */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR    = 1;
    // const GLuint VERTEX_ATTR_TEXTURE = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    // glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

    /* --- Binding --- */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (const GLvoid*)(offsetof(Vertex3DColor, _color)));
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV), (const GLvoid*)(offsetof(Vertex3DUV, _coordTex)));

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

/* --- Textures ---

GLuint initTex(img::Image* boidsTexture)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, boidsTexture->width(), boidsTexture->height(), 0, GL_RGBA, GL_FLOAT, boidsTexture->data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}*/

/* --- Draw --- */

void drawOpenGL(GLuint vao)
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void drawOpenGLSkybox(GLuint vao)
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void drawOpenGLBoids(GLuint vao /* GLuint texture */)
{
    glBindVertexArray(vao);
    // glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    // glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}