#include <cstdlib>
#include <vector>
#include "Boids.hpp"
#include "Parameters.hpp"
#include "Tracker.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

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

    // App
    auto ctx = p6::Context{{.title = "Projet"}};
    ctx.maximize_window();

    /***************************
     *   INITIALIZATION CODE   *
     ***************************/

    Boids   boids(Parameters::get());
    Tracker trackSquare(
        glm::vec2(p6::random::number(-0.05f, -0.05f), p6::random::number(-1.f, 1.f)),
        0.01f,
        glm::vec2(0., 0.),
        glm::vec2(0., 0.)
    );

    /* --- VBO --- */
    /*
    // Creation vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Binding vbo sur cible GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //  Creation tab coordonnee
    GLfloat vertices[] = {-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f};

    // Envoi donnee
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    // Debinder
    glBindBuffer(GL_ARRAY_BUFFER, 0); */

    /* --- VAO --- */

    /*

    // Creation vao
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // Binding vao
    glBindVertexArray(vao);

    // Activer attribut position
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

    // Rebinder vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Specifier format position
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

    // Debind vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Debind vao
    glBindVertexArray(0); */

    /**************************
     *     RENDERING CODE     *
     **************************/

    ctx.imgui = [&]() {
        /* Parameters' window */
        ImGui::Begin("Test");

        ImGui::SliderInt("Square number", &Parameters::get().SQUARE_NB, 10, Parameters::get().MAX_SQUARE_NB);
        ImGui::SliderFloat("Max speed", &Parameters::get().MAX_SPEED, 0.1, 1.);
        ImGui::SliderFloat("Min distance of cohesion", &Parameters::get().MIN_DIST, 0.1, 1.);
        ImGui::SliderFloat("Attraction", &Parameters::get().FACTOR_ATTRACTION, 0.001, 0.01);
        ImGui::SliderFloat("Repulsion", &Parameters::get().FACTOR_REPULSION, -0.2, -0.001);
        ImGui::SliderFloat("Max Repulsion", &Parameters::get().MAX_REPULSION, -1.f, -4.f);
        ImGui::SliderFloat("Attraction tracker", &Parameters::get().FACTOR_ATTRACT_TRACKER, 0.01f, 0.3f);

        ImGui::End();
    };

    // Infinite update loop
    ctx.update = [&]() {
        /*
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT); */

        ctx.background(p6::NamedColor::RaspberryGlace);

        /*
        // Bind vao
        glBindVertexArray(vao);

        // Draw call
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Debind vao
        glBindVertexArray(0); */

        // Tracker
        trackSquare.drawTracker(ctx);
        trackSquare.updatePositionTracker();

        // Boids
        boids.updateBoidsAcc(&trackSquare, Parameters::get());
        boids.drawBoids(ctx, Parameters::get());
    };

    ctx.start();
    /*
        // Free vbo
        glDeleteBuffers(1, &vbo);

        // Free vao
        glDeleteVertexArrays(1, &vao); */
}
