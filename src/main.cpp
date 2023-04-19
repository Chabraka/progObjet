#include <cstdlib>
#include <vector>
#include "Boids.hpp"
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

    // Actual app
    auto ctx = p6::Context{{.title = "Projet"}};
    ctx.maximize_window();

    /***************************
     *   INITIALIZATION CODE   *
     ***************************/

    Boids boids(50, 100, 0.01f, 0.5f, 0.7f, 0.001f, -0.02f, -3.f);

    /**************************
     *     RENDERING CODE     *
     **************************/

    ctx.imgui = [&]() {
        /* Parameters' window */
        ImGui::Begin("Test");
        /* Number of squares */
        // ImGui::SliderInt("Square number", &squareNumber, 10, 100);
        ImGui::SliderInt("Square number", &boids._squareNumber, 10, boids._maxSquareNumber);

        ImGui::SliderFloat("max speed", &boids._maxSpeed, 0.1, 1.);

        ImGui::SliderFloat("min distance/cohesion", &boids._minDistance, 0.1, 1.);

        ImGui::SliderFloat("Attraction", &boids._factorAttraction, 0.001, 0.01);

        ImGui::SliderFloat("Repulsion", &boids._factorRepulsion, -0.2, -0.001);

        ImGui::SliderFloat("max Repulsion", &boids._maxRepulsion, -1.f, -4.f);
        ImGui::End();
    };

    Square trackSquare(
        glm::vec2(p6::random::number(-2.f, 2.f), p6::random::number(-1.f, 1.f)),
        0.01f,
        glm::vec2(0., 0.),
        glm::vec2(0., 0.)
    );

    // Infinite update loop
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::RaspberryGlace);

        drawSquare(trackSquare, ctx);

        updatePositionTracker(&trackSquare);

        boids.updateBoidsAcc(&trackSquare);
        boids.drawBoids(ctx);
    };

    ctx.start();
}
