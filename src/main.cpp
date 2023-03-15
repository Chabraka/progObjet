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


    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/
    Square square(glm::vec2(p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f)), 0.05f);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::RaspberryGlace);

        drawSquare(square, ctx);
<<<<<<< HEAD
        square.center.x += p6::random::number(-0.001f, 0.001f);
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
=======
        square.center.x += p6::random::number(-0.01f, 0.01f);
        square.center.y += p6::random::number(-0.01f, 0.01f);
>>>>>>> eba520ec6328a7c4c9403f4b2947b75d57d6e28e
    };
 

    ctx.start();

   
}