#include <cstdlib>
#include <vector>
#include "glm/fwd.hpp"
#include "imgui.h"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "Square.hpp"
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

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    int                 squareNumber    = 50;
    int                 maxSquareNumber = 100;
    std::vector<Square> boids;

    for (int i = 0; i < maxSquareNumber; i++)
    {
        Square square(
            glm::vec2(p6::random::number(-2.f, 2.f), p6::random::number(-1.f, 1.f)),
            0.05f,
            glm::vec2(p6::random::number(-0.02f, 0.02f), p6::random::number(-0.02f, 0.02f)),
            glm::vec2(0., 0.),
            0.3,
            0.1

        );
        boids.push_back(square);
    }

    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    ctx.imgui = [&]() {
        // Window
        ImGui::Begin("Test");
        ImGui::SliderInt("Square number", &squareNumber, 10, 100);

        /*jouer avec les valeurs repulsion + maxRepulsion et attraction, factorSpeedMean, minimal distance*/
        
        ImGui::SliderFloat("Square speed x", &boids[1]._speed.x, -0.5f, 0.5f);
        ImGui::SliderFloat("Square speed y", &boids[1]._speed.y, -0.5f, 0.5f);
        /*min et max speed ne doit pas être dans le négatif ni passer par 0 ! */
        ImGui::SliderFloat("Square max speed", &boids[1]._maxSpeed, -1.f, 1.f);
        ImGui::SliderFloat("Square min speed", &boids[1]._minSpeed, -0.5f, 0.5f);
        ImGui::End();
    };

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::RaspberryGlace);

        updateBoidsAcc(&boids);

        for (int j = 0; j < squareNumber; j++)
        {
            drawSquare(boids[j], ctx);
            boids[j].updatePosition();
        }
    };

    ctx.start();
}
