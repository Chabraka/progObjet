#include <cstdlib>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Boids/Boids.hpp"
#include "Camera/TrackballCamera.hpp"
#include "Obstacles/Islands.hpp"
#include "Obstacles/MainIsland.hpp"
#include "OpenGL/OpenGL.hpp"
#include "Walker/Walker.hpp"
#include "imgui.h"
#define DOCTEST_CONFIG_IMPLEMENT

#include <Lmodel.hpp>
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
    img::Image skyTex     = p6::load_image_buffer("assets/textures/skybox.png");

    /***************************
     *   INITIALIZATION CODE   *
     ***************************/

    // Skybox
    Skybox skybox(Parameters::get());
    GLuint vaoS = initOpenGLSkybox(Parameters::get().BOX_SIZE);
    GLuint texS = initTex(skyTex);

    // Walker
    Walker walker(&shaderTex);

    // Cam
    MatrixView      matrixView;
    TrackballCamera camera;

    // Islands
    MainIsland  mainIsland(&shaderTex);
    Islands islands(50, Parameters::get().BOX_SIZE, 3.0, 0.4, &shaderTex);

    // Boids
    Boids  boids(Parameters::get(), 3.0,0.4, &shaderTex, glm::vec3(0.020588, 0.045294, 0.150000) , glm::vec3(5.000000, 5.000000, 5.000000), 150.000000);
    //GLuint vaoB = initOpenGLBoids();

    // Tracker
    Tracker tracker(
        0.08f,
        glm::vec3(p6::random::number(-0.05f, -0.05f), p6::random::number(-1.f, 1.f), p6::random::number(-1.f, 1.f)),
        glm::vec3(0.3),
        glm::vec3(0.2)
    );
    GLuint vaoT = initOpenGLTracker();

    // Loaded model
    // pour test
    // Model model("assets/models/main_island.obj", "assets/textures/floating_island.png", &shaderTex);
    //Model model;
    //model._vertex_size  = 2961;
    //GLuint vaomodel     = initOpenGLModel();
    //GLuint modelTexture = initTex(modelImage);

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


    auto start = std::chrono::high_resolution_clock::now();

    // Infinite update loop
    ctx.update = [&]() {
        // mesure du temps écoulé pour une boucle
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        float dt = elapsed.count();
        start = end;
        // std::cout << "Temps de rendu : " << renderTime << " secondes" << std::endl;
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

        glm::mat4 lightModelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(1,2,3));
        // lightModelMatrix = glm::scale(lightModelMatrix, glm::vec3(0.2f));
        glm::vec4 lightdirection = (matView*lightModelMatrix*glm::vec4(1.f,0.f,0.f,1.f));

        // Islands
        // Islands
        shader.use();
        mainIsland.drawIsland(&shaderTex, matrixView._ProjMatrix, matView);
        islands.drawIslands(matrixView._ProjMatrix, matView, walker.getCenter());

        // Tracker
        tracker.updatePositionTracker(Parameters::get());
        tracker.drawTracker(&shader, matrixView._ProjMatrix, matView, vaoT);

        // Boids
        boids.updateBoidsAcc(&tracker, Parameters::get());
        std::cout << walker.getCenter().x << walker.getCenter().y << walker.getCenter().z << " " << (float) camera.m_fDistance << std::endl;
        boids.drawBoids(matrixView._ProjMatrix, matView, Parameters::get(), dt, walker.getCenter(), lightdirection, glm::vec3(1));

        // Walker
        walker.updatePosition(ctx, Parameters::get().BOX_SIZE, boids._boids, islands._islands);
        walker.drawWalker(&shaderTex, matrixView._ProjMatrix, matView);

        // Skybox
        shaderTex.use();
        skybox.drawSkybox(&shaderTex, matrixView._ProjMatrix, matView, vaoS, texS);

        
        // loaded model
        // shaderTex.use();
        // model.drawModel(&shaderTex, matrixView._ProjMatrix, matView);

        // Camera
        camera.updatePosition(walker.getCenter(), Parameters::get().BOX_SIZE);
        cameraControls(ctx, camera);
        ctx.mouse_scrolled = [&](p6::MouseScroll scroll) {
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
