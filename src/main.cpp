#include <cstdlib>
#include <string>
#include <vector>
#include "Boids/Boids.hpp"
#include "GLFW/glfw3.h"
#include "Islands/Islands.hpp"
#include "OpenGL.hpp"
#include "imgui.h"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "Camera.hpp"
#include "Loader.hpp"
#include "doctest/doctest.h"

int main(int argc, char* argv[])
{
    opentest("../models/test");

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

    // Texture
    // img::Image sheetTex = p6::load_image_buffer("assets/textures/boids/sheet.jpg");

    // Shaders
    const p6::Shader shader = p6::load_shader("shaders/3D.vs.glsl", "shaders/3D.fs.glsl");
    glEnable(GL_DEPTH_TEST);

    /***************************
     *   INITIALIZATION CODE   *
     ***************************/

    // Cam
    MatrixView    matrixView;
    FreeflyCamera camera;

    // Islands
    Island  mainIsland(glm::vec3(0.0, 0.0, 0.0));
    GLuint  vaoI = initOpenGLMainIsland();
    Islands islands(25);
    GLuint  vaoIs = initOpenGLIslands();

    // Boids
    Boids  boids(Parameters::get());
    GLuint vaoB = initOpenGLBoids();
    // GLuint texB = initTex(&sheetTex);

    // Tracker
    Tracker tracker(
        glm::vec3(p6::random::number(-0.05f, -0.05f), p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f)),
        0.08f,
        glm::vec3(0.3),
        glm::vec3(0.2)
    );
    GLuint vaoT = initOpenGLTracker();

    /**************************
     *     RENDERING CODE     *
     **************************/

    ctx.imgui = [&]() {
        /* Parameters' window */
        ImGui::Begin("Parameters");

        ImGui::SliderInt("Boids number", &Parameters::get().BOID_NB, 10, Parameters::get().MAX_BOID_NB);
        ImGui::SliderFloat("Max speed", &Parameters::get().MAX_SPEED, 0.1, 1.);
        ImGui::SliderFloat("Min distance of cohesion", &Parameters::get().MIN_DIST, 0.1, 1.);
        ImGui::SliderFloat("Attraction", &Parameters::get().FACTOR_ATTRACTION, 0.001, 0.01);
        ImGui::SliderFloat("Repulsion", &Parameters::get().FACTOR_REPULSION, -0.2, -0.001);
        ImGui::SliderFloat("Max Repulsion", &Parameters::get().MAX_REPULSION, -1.f, -4.f);
        ImGui::SliderFloat("Attraction (tracker)", &Parameters::get().FACTOR_ATTRACT_TRACKER, 0.01f, 0.3f);

        ImGui::End();
    };

    // Infinite update loop
    ctx.update = [&]() {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        // Camera power Matrix
        matrixView._MMatrix = glm::mat4(1);
        // matrixView._MVPMatrix =  matrixView._ProjMatrix * matrixView._MMatrix;

        // // Matrix
        // shader.set("uMVMatrix", matrixView._MMatrix);
        // shader.set("uMVPMatrix", matrixView._MVPMatrix);
        // shader.set("uNormalMatrix", matrixView._NormalMatrix);

        // Islands
        mainIsland.drawIsland(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaoI);
        islands.drawIslands(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaoIs);

        // Tracker
        tracker.updatePositionTracker();
        tracker.drawTracker(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaoT);

        // Boids
        boids.updateBoidsAcc(&tracker, Parameters::get());
        boids.drawBoids(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaoB, /* texB, */ Parameters::get());

        // Quit
        if (ctx.key_is_pressed(GLFW_KEY_ESCAPE))
        {
            ctx.stop();
        };

        // Camera
        cameraControls(ctx, camera);
        // arrive pas a mettre dans Controls :'-(
        ctx.mouse_dragged = [&](const p6::MouseDrag& button) {
            camera.rotateLeft(button.delta.x * 50);
            camera.rotateUp(-button.delta.y * 50);
        };
    };

    ctx.start();
}
