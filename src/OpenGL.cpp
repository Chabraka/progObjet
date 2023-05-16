#include "OpenGL.hpp"

glm::mat4 translate(float tx, float ty, float tz)
{
    return glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(tx, ty, tz, 1));
}

GLuint initOpenGL()
{
    /* --- VBO --- */
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //  Tab with coordinates
    Vertex2DColor tracker[] = {
        Vertex2DColor(glm::vec3(-0.05, -0.05, -0.05), glm::vec3(1, 0, 0)),
        Vertex2DColor(glm::vec3(-0.05, 0.05, -0.05), glm::vec3(0, 1, 0)),
        Vertex2DColor(glm::vec3(0.05, -0.05, -0.05), glm::vec3(0, 0, 1)),
        Vertex2DColor(glm::vec3(0.05, 0.05, -0.05), glm::vec3(1, 0, 0)),
        Vertex2DColor(glm::vec3(-0.05, 0.05, -0.05), glm::vec3(0, 1, 0)),
        Vertex2DColor(glm::vec3(0.05, -0.05, -0.05), glm::vec3(0, 0, 1)),
    };

    /* Vertex2DColor paperplane[] = {
        Vertex2DColor(glm::vec3(   ,   ,   ), glm::vec3(1, 0, 0)),

    }; */

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DColor), tracker, GL_STATIC_DRAW);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)(offsetof(Vertex2DColor, _position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)(offsetof(Vertex2DColor, _color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

void drawOpenGL(GLuint vao)
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}