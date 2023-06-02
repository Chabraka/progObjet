#include <cstdlib>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Boids/Boids.hpp"
#include "Camera/TrackballCamera.hpp"
#include "Light.hpp"
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
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0;
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // App
    auto ctx = p6::Context{{.title = "Flying Whales"}};
    ctx.maximize_window();

    // Shaders
    const p6::Shader shader       = p6::load_shader("shaders/3D.vs.glsl", "shaders/3D.fs.glsl");
    const p6::Shader shaderTex    = p6::load_shader("shaders/tex3D.vs.glsl", "shaders/tex3D.fs.glsl");
    const p6::Shader shaderSkybox = p6::load_shader("shaders/tex3D.vs.glsl", "shaders/skybox.fs.glsl");
    shaderTex.set("uTexture", 0);
    glEnable(GL_DEPTH_TEST);

    // Texture
    img::Image skyTex = p6::load_image_buffer("assets/textures/skybox.png");

    /***************************
     *   INITIALIZATION CODE   *
     ***************************/

    // Skybox
    Skybox skybox(Parameters::get());
    GLuint vaoS = initOpenGLSkybox(Parameters::get().BOX_SIZE);
    GLuint texS = initTex(skyTex);

    // Walker
    Walker walker(&shaderTex, LightProperties(glm::vec3(1), glm::vec3(0), 0.f));

    // Cam
    MatrixView      matrixView;
    TrackballCamera camera;

    // Islands
    MainIsland mainIsland(&shaderTex);
    Islands    islands(50, Parameters::get().BOX_SIZE, Parameters::get().FLOOR_LOW_MEDIUM, Parameters::get().FLOOR_MEDIUM_HIGH, &shaderTex, LightProperties(glm::vec3(1), glm::vec3(0), 0.f));

    // Boids
    Boids boids(&shaderTex, LightProperties(glm::vec3(1), glm::vec3(0), 0.f));

    /**************************
     *     RENDERING CODE     *
     **************************/

    ctx.imgui = [&]() {
        /* Parameters' window */
        boidsImGui();
    };

    auto start = std::chrono::high_resolution_clock::now();

    // Infinite update loop
    ctx.update = [&]() {
        // Time elapsed in a loop
        auto                          end     = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        float                         dt      = elapsed.count();
        start                                 = end;

        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera power Matrix
        matrixView._MMatrix = glm::mat4(1);
        glm::mat4 matView   = camera.getViewMatrix(walker);

        // Light
        glm::mat4 lightModelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(3, 3, 3));
        glm::vec4 lightposition    = (lightModelMatrix * glm::vec4(0.f, 0.f, 0.f, 1.f));
        glm::vec3 lightIntensity   = glm::vec3(50);
        Light     sun(glm::vec3(lightposition), lightIntensity);

        // Islands
        shaderTex.use();
        mainIsland.drawIsland(&shaderTex, matrixView._ProjMatrix, matView, sun, walker.getLight());
        islands.drawIslands(matrixView._ProjMatrix, matView, walker.getCenter(), sun, walker.getLight());

        // Boids
        boids.updateBoidsAcc();
        boids.drawBoids(matrixView._ProjMatrix, matView, dt, walker.getCenter(), boids._boids, islands._islands, mainIsland, sun, walker.getLight());

        // Walker
        walker.updatePosition(ctx, Parameters::get().BOX_SIZE, Parameters::get(), boids._boids, islands._islands, mainIsland);
        walker.drawWalker(&shaderTex, matrixView._ProjMatrix, matView, lightposition, lightIntensity);

        // Skybox
        shaderSkybox.use();
        skybox.drawSkybox(&shaderSkybox, matrixView._ProjMatrix, matView, vaoS, texS);

        // Camera
        camera.updatePosition(walker.getCenter(), walker.getOrientation(), Parameters::get().BOX_SIZE);
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
