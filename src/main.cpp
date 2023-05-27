#include <cstdlib>
#include <string>
#include <vector>
#include "Boids/Boids.hpp"
#include "Camera/TrackballCamera.hpp"
#include "Obstacles/Islands.hpp"
#include "OpenGL/OpenGL.hpp"
#include "Walker/Walker.hpp"
#include "imgui.h"
#define DOCTEST_CONFIG_IMPLEMENT

#include <Lmodel.hpp>
#include <Loader/Loader.hpp>
#include <common.hpp>
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
    img::Image modelImage = p6::load_image_buffer("assets/textures/uvgrid.jpg");

    /***************************
     *   INITIALIZATION CODE   *
     ***************************/

    // Skybox
    Skybox skybox(Parameters::get());
    GLuint vaoS = initOpenGLSkybox(Parameters::get().BOX_SIZE);
    GLuint texS = initTex(skyTex);

    // Walker
    Walker walker;
    GLuint vaoW = initOpenGLTracker();

    // Cam
    MatrixView      matrixView;
    TrackballCamera camera;

    // Islands
    Island  mainIsland;
    GLuint  vaoI = initOpenGLMainIsland();
    Islands islands(50, Parameters::get().BOX_SIZE);
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
     Model model;
    model._vertex_size=2961;
    GLuint vaomodel = initOpenGLModel();
    GLuint modelTexture = initTex(modelImage);


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
        glm::mat4 matView = camera.getViewMatrix(walker);

        // // Matrix
        // shader.set("uMVMatrix", matrixView._MMatrix);
        // shader.set("uMVPMatrix", matrixView._MVPMatrix);
        // shader.set("uNormalMatrix", matrixView._NormalMatrix);

        // Islands
        shader.use();
        mainIsland.drawIsland(&shader, matrixView._ProjMatrix, matView, vaoI);
        islands.drawIslands(&shader, matrixView._ProjMatrix, matView, vaoIs);

        // Tracker
        tracker.updatePositionTracker(Parameters::get());
        tracker.drawTracker(&shader, matrixView._ProjMatrix, matView, vaoT);

        // Boids
        boids.updateBoidsAcc(&tracker, Parameters::get());
        boids.drawBoids(&shader, matrixView._ProjMatrix, matView, vaoB, Parameters::get());

        // Walker
        walker.updatePosition(ctx, Parameters::get().BOX_SIZE);
        walker.drawWalker(&shader, matrixView._ProjMatrix, matView, vaoW);

        // Skybox
        shaderTex.use();
        skybox.drawSkybox(&shaderTex, matrixView._ProjMatrix, matView, vaoS, texS);

        // loaded model
           // // loaded model
        shaderTex.use();
        model.drawModel(&shaderTex, matrixView._ProjMatrix, matView, vaomodel, modelTexture);

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
