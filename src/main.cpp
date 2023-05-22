#include <string>
#include <cstdlib>
#include <vector>
#include "Boids.hpp"
#include "GLFW/glfw3.h"
// #include "Island.hpp"
#include "OpenGL.hpp"
#include "imgui.h"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "Loader.hpp"
#include "Camera.hpp"


int main(int argc, char* argv[])
{


	opentest("../models/test");

	//return 0;




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
    GLuint     vaoB = initOpenGLBoids();

    // const uint nbTriangles = 100;
    // Island     island(glm::vec3(0.0, 0.0, 0.0), 0.8);
    // GLuint     vaoI = initOpenGLIsland(island._radius, nbTriangles);

    Boids   boids(Parameters::get());
    Tracker tracker(
        glm::vec3(p6::random::number(-0.05f, -0.05f), p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f)),
        0.08f,
        glm::vec3(0.3),
        glm::vec3(0.2)
    );

    FreeflyCamera camera;

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

        //Camera power Matrix

        matrixView._MMatrix = glm::mat4(1);
        // matrixView._MVPMatrix =  matrixView._ProjMatrix * matrixView._MMatrix;


        // // Matrix
        // shader.set("uMVMatrix", matrixView._MMatrix);
        // shader.set("uMVPMatrix", matrixView._MVPMatrix);
        // shader.set("uNormalMatrix", matrixView._NormalMatrix);

        // Island
        // island.drawIsland(&shader, matrixView._ProjMatrix, vaoI, nbTriangles);

        // Tracker
        tracker.updatePositionTracker();
        tracker.drawTracker(&shader, matrixView._ProjMatrix, vaoB);

        // Boids
        boids.updateBoidsAcc(&tracker, Parameters::get());
        boids.drawBoids(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaoB, Parameters::get());

        // Quit
        if (ctx.key_is_pressed(GLFW_KEY_ESCAPE))
        {
            ctx.stop();
        };

        //Camera

        ctx.key_pressed = [&](const p6::Key& key) {
            if (key.physical == GLFW_KEY_W)
            {
                camera.moveFront(0.1);
            }
            if (key.physical == GLFW_KEY_S)
            {
                camera.moveFront(-0.1);
            }
			if (key.physical == GLFW_KEY_A)
            {
                camera.moveLeft(0.1);
            }
			if (key.physical == GLFW_KEY_D)
            {
                camera.moveLeft(-0.1);
            }
        };


        ctx.mouse_dragged = [&](const p6::MouseDrag& button) {
            camera.rotateLeft(button.delta.x * 50);
            camera.rotateUp(-button.delta.y * 50);
        };


    };

    ctx.start();
}
