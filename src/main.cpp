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

    // Actual app
    auto ctx = p6::Context{{.title = "Projet"}};
    ctx.maximize_window();

    /***************************
     *   INITIALIZATION CODE   *
     ***************************/

    Boids   boids(Parameters::get());
    Tracker trackSquare(
        glm::vec2(p6::random::number(-2.f, 2.f), p6::random::number(-1.f, 1.f)),
        0.01f,
        glm::vec2(0., 0.),
        glm::vec2(0., 0.)
    );

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
        ctx.background(p6::NamedColor::RaspberryGlace);

        // Tracker
        trackSquare.drawSquare(ctx);
        trackSquare.updatePositionTracker();

        // Boids
        boids.updateBoidsAcc(&trackSquare, Parameters::get());
        boids.drawBoids(ctx, Parameters::get());
    };

    ctx.start();
}
