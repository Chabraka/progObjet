#pragma once

#include <vector>
#include <string>
// #include <GL/glew.h>
#include <glm/vec3.hpp>


void linetofloats(const std::string& str, std::vector<glm::vec3>& v);

void readVertices(const std::string& path, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& texv, std::vector<glm::vec3>& normalv);

void readFaces(const std::string& path, std::vector<int>& vertices, std::vector<int>& texv, std::vector<int>& normalv);

