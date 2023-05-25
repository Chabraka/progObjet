#include <cstdlib>
#include <string>
#include <vector>
#include "Boids/Boids.hpp"
#include "Islands/Islands.hpp"
#include "OpenGL/OpenGL.hpp"
#include "Skybox/Skybox.hpp"
#include "Walker/Walker.hpp"
#include "imgui.h"
#define DOCTEST_CONFIG_IMPLEMENT

#include <Lmodel.hpp>
#include <Loader/Loader.hpp>
#include <common.hpp>
#include "TrackballCamera.hpp"
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
    const p6::Shader shader    = p6::load_shader("shaders/3D.vs.glsl", "shaders/3D.fs.glsl");
    const p6::Shader shaderTex = p6::load_shader("shaders/tex3D.vs.glsl", "shaders/tex3D.fs.glsl");
    shaderTex.set("uTexture", 0);
    glEnable(GL_DEPTH_TEST);

    // Texture
    img::Image skyTex = p6::load_image_buffer("assets/textures/skybox.png");

    /***************************
     *   INITIALIZATION CODE   *
     ***************************/

    // Cam
    MatrixView      matrixView;
    TrackballCamera camera;

    // Skybox
    Skybox skybox;
    GLuint vaoS = initOpenGLSkybox();
    GLuint texS = initTex(skyTex);

    // Walker
    Walker walker;
    GLuint vaoW = initOpenGLTracker();

    // Islands
    Island  mainIsland(glm::vec3(0.0, 0.0, 0.0));
    GLuint  vaoI = initOpenGLMainIsland();
    Islands islands(50);
    GLuint  vaoIs = initOpenGLIslands();

    // Boids
    Boids  boids(Parameters::get());
    GLuint vaoB = initOpenGLBoids();

    // Tracker
    Tracker tracker(
        0.08f,
        glm::vec3(p6::random::number(-0.05f, -0.05f), p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f)),
        glm::vec3(0.3),
        glm::vec3(0.2)
    );
    GLuint vaoT = initOpenGLTracker();

    // Loaded model
    Model  model;
    GLuint vaomodel = initOpenGLModel();

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

        // Camera power Matrix
        matrixView._MMatrix = glm::mat4(1);
        // matrixView._MVPMatrix =  matrixView._ProjMatrix * matrixView._MMatrix;

        // // Matrix
        // shader.set("uMVMatrix", matrixView._MMatrix);
        // shader.set("uMVPMatrix", matrixView._MVPMatrix);
        // shader.set("uNormalMatrix", matrixView._NormalMatrix);

        // Islands
        shader.use();
        mainIsland.drawIsland(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaoI);
        islands.drawIslands(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaoIs);

        // Tracker
        tracker.updatePositionTracker();
        tracker.drawTracker(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaoT);

        // Boids
        boids.updateBoidsAcc(&tracker, Parameters::get());
        boids.drawBoids(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaoB, Parameters::get());

        // Walker
        walker.updatePosition(ctx);
        walker.drawWalker(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaoW);

        // Skybox
        shaderTex.use();
        skybox.drawSkybox(&shaderTex, matrixView._ProjMatrix, camera.getViewMatrix(), vaoS, texS);

        // loaded model
        model.drawModel(&shader, matrixView._ProjMatrix, camera.getViewMatrix(), vaomodel);

        // Camera
        cameraControls(ctx, camera);
        ctx.mouse_scrolled = [&](const p6::MouseScroll& scroll) {
            (scroll.dy > 0) ? camera.moveFront(-0.1) : camera.moveFront(0.1); // Zoom when scrolling
        };

        // Quit
        if (ctx.key_is_pressed(GLFW_KEY_ESCAPE))
        {
            ctx.stop();
        };
    };
    ctx.start();
}
