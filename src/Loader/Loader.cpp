#include "Loader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


void linetofloats(const std::string& str, std::vector<glm::vec3>& v) {
    std::istringstream iss(str);
    glm::vec3 vec;
    iss >> vec.x;
    iss >> vec.y;
    iss >> vec.z;

    v.push_back(vec);
}

void readVertices(const std::string& path, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& texv, std::vector<glm::vec3>& normalv) {
    std::ifstream file(path);

    vertices.clear();
    texv.clear();
    normalv.clear();

    std::string line;
    size_t pos;
    while (std::getline(file, line)) {
        if ((pos = line.find("v ")) != std::string::npos) {
            linetofloats(line.substr(pos + 2), vertices);
        } else if ((pos = line.find("vt ")) != std::string::npos) {
            linetofloats(line.substr(pos + 3), texv);
        } else if ((pos = line.find("vn ")) != std::string::npos) {
            linetofloats(line.substr(pos + 3), normalv);
        }
    }
}

void readFaces(const std::string& path, std::vector<int>& vertices, std::vector<int>& texv, std::vector<int>& normalv) {
    std::ifstream file(path);

    vertices.clear();
    texv.clear();
    normalv.clear();

    int v1, v2, v3, vt1, vt2, vt3, vn1, vn2, vn3;

    std::string line;
    size_t pos;
    while (std::getline(file, line)) {
        if ((pos = line.find("f ")) != std::string::npos) {
            sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
            vertices.push_back(v1);
            vertices.push_back(v2);
            vertices.push_back(v3);
            texv.push_back(vt1);
            texv.push_back(vt2);
            texv.push_back(vt3);
            normalv.push_back(vn1);
            normalv.push_back(vn2);
            normalv.push_back(vn3);
        }
    }
}


