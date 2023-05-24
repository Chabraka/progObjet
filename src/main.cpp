#include <cstdlib>
#include <string>
#include <vector>
#include "Boids/Boids.hpp"
#include "GLFW/glfw3.h"
#include "Islands/Islands.hpp"
#include "OpenGL/OpenGL.hpp"
#include "Skybox/Skybox.hpp"
#include "imgui.h"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT

#include <Loader/Loader.hpp>

#include "Camera.hpp"
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
    MatrixView    matrixView;
    FreeflyCamera camera;

    // Skybox
    Skybox skybox;
    GLuint vaoS = initOpenGLSkybox();
    GLuint texS = initTex(skyTex);

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

    //Test model

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> texv;
    std::vector<glm::vec3> normalv;

    readVertices("../assets/models/cube.obj", vertices, texv,normalv );

    // GLuint vbo;
    // glGenBuffers(1, &vbo);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // GLuint vao;
    // glGenVertexArrays(1, &vao);

    // glBindVertexArray(vao);

    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);
    // glEnableVertexAttribArray(2);


    // glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // GLint myLoc;
    // GLint myNormal;
    // GLint myCoords;

    // GLint uMVPMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    
    // GLint uMVMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    // GLint uNormalMatrixLoc =glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    // myLoc = glGetUniformLocation(program.getGLId(), "vPosition_vs");
    // myNormal = glGetUniformLocation(program.getGLId(), "vNormal_s");
    // myCoords= glGetUniformLocation(program.getGLId(), "vPTexCoords_vs");


    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)(offsetof(ShapeVertex, position)));
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)(offsetof(ShapeVertex, normal)));
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)(offsetof(ShapeVertex, texCoords)));

    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // glBindVertexArray(0);

   

    // glEnable(GL_DEPTH_TEST);
    

    // glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)(800/600), 0.1f,100.f);

    // glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0.,0.,-5.));

    // glm::mat4 NormalMatrix=glm::transpose(glm::inverse(MVMatrix));



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

        // Skybox
        shaderTex.use();
        skybox.drawSkybox(&shaderTex, matrixView._ProjMatrix, camera.getViewMatrix(), vaoS, texS);

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
