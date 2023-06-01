#include "Boids.hpp"

/* ----- Constructor ----- */
Boids::Boids(Parameters& params, float floor_low_medium, float floor_medium_high, const p6::Shader* shader, LightProperties lightprop):Boids(params, floor_low_medium, floor_medium_high, shader){
		light = lightprop;
}


Boids::Boids(Parameters& params, float floor_low_medium, float floor_medium_high, const p6::Shader* shader)
{

    this->renderer = MultiResObjRenderer("assets/models/baleine_low.obj", "assets/models/baleine_medium.obj", "assets/models/baleine_high.obj",
        "assets/textures/baleine.jpg", shader,
        floor_low_medium, floor_medium_high);
    // Creation of boids
    for (int i = 0; i < params.MAX_BOID_NB; i++)
    {
        Boid boid(
            0.3f,                                                                                                                                                                                                                                 // radius
            glm::vec3(p6::random::number(-(params.BOX_SIZE - 0.3f), (params.BOX_SIZE - 0.3f)), p6::random::number(-(params.BOX_SIZE - 0.3f), (params.BOX_SIZE - 0.3f)), p6::random::number(-(params.BOX_SIZE - 0.3f), (params.BOX_SIZE - 0.3f))), // center
            glm::vec3(p6::random::number(-params.MAX_SPEED, params.MAX_SPEED)),                                                                                                                                                                   // speed
            glm::vec3(0.0)                                                                                                                                                                                                                        // acceleration
        );
        _boids.push_back(boid);
    }
}

/* ----- Draw ----- */


//collision boid
void Boids::drawBoids(glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, Parameters& params, float dt, glm::vec3 cam_position, const std::vector<Boid>& boids, const std::vector<Island>& islands, const MainIsland& mainIsland,Light sun, Light walker)

{
    for (int j = 0; j < params.BOID_NB; j++)
    {
        float cam_distance = glm::distance(_boids[j]._center, cam_position);
        // std::cout << cam_distance <<"=cam_distance" << std::endl;

        this->drawBoid(&_boids[j],ProjMatrix, ViewMatrix, cam_distance, sun, walker);
        _boids[j].updatePosition(params, dt, boids, islands, mainIsland);
    }
}

void Boids::drawBoid(Boid *boid, glm::mat4 ProjMatrix, glm::mat4 ViewMatrix, float cam_distance, Light sun, Light walker)
{

    glm::mat4 T = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
    T           = glm::translate(T, boid->getCenter());
    // Orientation du boid:
    glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), -boid->_speed));
    float angle = glm::acos(glm::dot(glm::vec3(0.0f, 0.0f, -1.0f), -boid->_speed));
    T           = glm::rotate(T, angle, axis);

	this->renderer.low_renderer.shader->use();
    this->renderer.low_renderer.shader->set("uMVMatrix", T);
    this->renderer.low_renderer.shader->set("uMVPMatrix", ProjMatrix * ViewMatrix * T);
    this->renderer.low_renderer.shader->set("uNormalMatrix", glm::transpose(glm::inverse(T)));
    this->renderer.low_renderer.shader->set("uColor", glm::vec3(0.5, 0.8, 0.2));

    this->renderer.low_renderer.shader->set("uKd", this->light.diffuse);
    this->renderer.low_renderer.shader->set("uKs", this->light.specular);
    this->renderer.low_renderer.shader->set("uShininess", this->light.shininess);


	this->renderer.low_renderer.shader->set("uSunPosition", sun.position);
    this->renderer.low_renderer.shader->set("uSunIntensity", sun.intensity);
	this->renderer.low_renderer.shader->set("uWalkerPosition", walker.position);
    this->renderer.low_renderer.shader->set("uWalkerIntensity", walker.intensity);

    this->renderer.draw(cam_distance);
}

/* ----- Updates ----- */
void Boids::updateBoidsAcc(Tracker* tracker, Parameters& params)
{
    for (int i = 0; i < params.BOID_NB; i++)
    {
        _boids.at(i).updateAcc(_boids, i, params.MIN_DIST, params.FACTOR_ATTRACTION, params.FACTOR_REPULSION, params.FACTOR_REPULSION, tracker, params.FACTOR_ATTRACT_TRACKER);
    }
}
