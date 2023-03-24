#include <cstdlib>
#include "glm/fwd.hpp"
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
    Square square(
        glm::vec2(p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f)),
        0.05f,
        glm::vec2(0, 0),
        glm::vec2(0.1, 0.1)
    );

    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::RaspberryGlace);

        drawSquare(square, ctx);
        square.updatePosition(ctx);
    };

    ctx.start();
}