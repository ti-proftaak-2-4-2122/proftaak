#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

class ObjModel
{
public:
    class Face
    {
    public:
        int pos[3];
        int normal[3];
    };

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<Face> faces;

    ObjModel(const std::string &fileName);
    std::string toString();
};

