#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "Square.hpp"
#include "doctest/doctest.h"

/*
struct Vertex2DColor {
    glm::vec2 position;
    glm::vec3 color;

    Vertex2DColor() = default;
    Vertex2DColor(glm::vec2 p, glm::vec3 c)
        : position(p), color(c){};
};
*/

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "Projet"}};
    ctx.maximize_window();

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    /* --- VBO --- */

    /*
    // Creation vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Binding vbo sur cible GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //  Creation tab coordonnees
    Vertex2DColor vertices[] = {
        Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(1, 0, 0)),
        Vertex2DColor(glm::vec2(-0.5, 0.5), glm::vec3(0, 1, 0)),
        Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(0, 0, 1)),
        Vertex2DColor(glm::vec2(0.5, 0.5), glm::vec3(1, 0, 0)),
        Vertex2DColor(glm::vec2(-0.5, 0.5), glm::vec3(0, 1, 0)),
        Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(0, 0, 1))};

    // Envoi donnee
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);

    // Debinder
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    */

    /* --- VAO --- */

    /*
    // Creation vao
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // Binding vao
    glBindVertexArray(vao);

    // Activer attribut position
    glEnableVertexAttribArray(3);

    // Activer attribut couleur
    glEnableVertexAttribArray(8);

    // Rebinder vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Specifier format position
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)(offsetof(Vertex2DColor, position)));

    // Specifier format color
    glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*)(offsetof(Vertex2DColor, color)));

    // Debind vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Debind vao
    glBindVertexArray(0);
    */

    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/
    Square square(glm::vec2(p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f)), 0.05f);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::RaspberryGlace);

        drawSquare(square, ctx);
        square.center.x += p6::random::number(-0.001f, 0.001f)
                               square.center.y += p6::random::number(-0.001f, 0.001f);

        /*
        ctx.square(
            p6::Center{p6::random::number(0.f, 1.f), p6::random::number(0.f, 1.f)},
            p6::Radius{0.1f}
        );

        ctx.fill = {1.f, 0.7f, 0.2f};
        */

        /*
        // Nettoyer fenetre
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind vao
        glBindVertexArray(vao);

        // Draw call
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Debind vao
        glBindVertexArray(0); */
    };

    /*
    // Free vbo
    glDeleteBuffers(1, &vbo);

    // Free vao
    glDeleteVertexArrays(1, &vao);
    */

    // Should be done last. It starts the infinite loop.
    ctx.start();
}