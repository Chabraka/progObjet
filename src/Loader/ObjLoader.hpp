#pragma once

/*
    loader of .obj files.

    Warning ! This simple parser support only triangulate faces.
              (Blender quaternon are not allowed. Select triangulate option when exporting model )
*/

#include <stddef.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "p6/p6.h"

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

static std::vector<ShapeVertex> LoadOBJ(const char* fileName)
{
    std::vector<glm::vec3> vPos;
    std::vector<glm::vec3> vNorm;
    std::vector<glm::vec2> vTex;
    std::vector<GLuint>    vPosInd;
    std::vector<GLuint>    vNormInd;
    std::vector<GLuint>    vTexInd;

    // Vertex array
    std::vector<ShapeVertex> vertices;

    std::stringstream ss;
    std::ifstream     inFile(fileName);
    std::string       line = "";
    std::string       word = "";
    glm::vec3         vec3Temp;
    glm::vec2         vec2Temp;
    GLint             tempGLint = 0;

    // Check error
    if (!inFile.is_open())
    {
        throw "ERROR::OBJLOADER::Could not open file.";
    }

    // Read one line
    while (std::getline(inFile, line))
    {
        // Get prefix of the line (v, vt, vn...)
        ss.clear();
        ss.str(line);
        ss >> word;

        if (word == "v")
        {
            ss >> vec3Temp.x >> vec3Temp.y >> vec3Temp.z;
            vPos.push_back(vec3Temp);
        }
        else if (word == "vt")
        {
            ss >> vec2Temp.x >> vec2Temp.y;
            vTex.push_back(vec2Temp);
        }
        else if (word == "vn")
        {
            ss >> vec3Temp.x >> vec3Temp.y >> vec3Temp.z;
            vNorm.push_back(vec3Temp);
        }
        else if (word == "f")
        {
            int read = 0;
            while (ss >> tempGLint)
            {
                if (read == 0)
                {
                    vPosInd.push_back(tempGLint);
                }
                else if (read == 1)
                {
                    vTexInd.push_back(tempGLint);
                }
                else if (read == 2)
                {
                    vNormInd.push_back(tempGLint);
                }
                if (ss.peek() == '/')
                {
                    read++;
                    ss.ignore(1, '/');
                }
                else if (ss.peek() == ' ')
                {
                    read++;
                    ss.ignore(1, ' ');
                }
                read %= 3;
            }
        }
        else
        {
        }
    }
    vertices.resize(vPosInd.size(), ShapeVertex());

    for (size_t i = 0; i < vPosInd.size(); i++)
    {
        vertices[i].position  = vPos[vPosInd[i] - 1];
        vertices[i].normal    = vNorm[vNormInd[i] - 1];
        vertices[i].texCoords = vTex[vTexInd[i] - 1];
    }
    std::cout << "OBJ file loaded" << std::endl;
    return vertices;
}