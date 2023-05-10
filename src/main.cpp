#include <cstdlib>
#include <vector>
#include "Boids.hpp"
#include "GLFW/glfw3.h"
#include "OpenGL.hpp"
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

    // Shaders
    const p6::Shader shader = p6::load_shader("shaders/3D.vs.glsl", "shaders/3D.fs.glsl");
    glEnable(GL_DEPTH_TEST);

    /***************************
     *   INITIALIZATION CODE   *
     ***************************/
    MatrixView matrixView;
    GLuint     vao = initOpenGL();

    Boids   boids(Parameters::get());
    Tracker tracker(
        glm::vec3(p6::random::number(-0.05f, -0.05f), p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f)),
        0.08f,
        glm::vec3(0.3),
        glm::vec3(0.2)
    );

    /**************************
     *     RENDERING CODE     *
     **************************/

    ctx.imgui = [&]() {
        /* Parameters' window */
        ImGui::Begin("Parameters");

        ImGui::SliderInt("Square number", &Parameters::get().BOID_NB, 10, Parameters::get().MAX_BOID_NB);
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
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        // Matrix
        shader.set("uMVMatrix", matrixView._MVMatrix);
        shader.set("uMVPMatrix", matrixView._MVPMatrix);
        shader.set("uNormalMatrix", matrixView._NormalMatrix);

        // Tracker
        tracker.updatePositionTracker();
        tracker.drawTracker(&shader, matrixView._ProjMatrix, vao);

        // Boids
        boids.updateBoidsAcc(&tracker, Parameters::get());
        boids.drawBoids(&shader, matrixView._ProjMatrix, vao, Parameters::get());

        // Quit
        if (ctx.key_is_pressed(GLFW_KEY_A))
        {
            ctx.stop();
        };
    };

    ctx.start();
}
