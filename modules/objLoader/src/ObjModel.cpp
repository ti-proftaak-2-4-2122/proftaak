#include "ObjModel.h"
#include <fstream>
#include <sstream>
#include <iostream>


ObjModel::ObjModel(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Could not open file " << fileName << std::endl;
        return;
    }
    std::string line;
    while (!file.eof())
    {
        std::getline(file, line);
        std::stringstream lineStream(line);

        std::string firstPart;
        lineStream >> firstPart;
        if (firstPart == "v")
        {
            glm::vec3 position(0, 0, 0);
            lineStream >> position.x;
            lineStream >> position.y;
            lineStream >> position.z;
            positions.push_back(position);
        }
        if (firstPart == "vn")
        {
            glm::vec3 normal(0, 0, 0);
            lineStream >> normal.x;
            lineStream >> normal.y;
            lineStream >> normal.z;
            normals.push_back(normal);
        }
        if (firstPart == "f")
        {
            Face face{};
            for (int i = 0; i < 3; i++)
            {
                char junk;
                lineStream >> face.pos[i];
                lineStream >> junk;
                lineStream >> face.normal[i];
                lineStream >> junk;
                lineStream >> face.normal[i];
                face.pos[i]--;
                face.normal[i]--;
            }
            faces.push_back(face);
        }
    }
    loadVertices();
}

std::string ObjModel::toString()
{
    std::ostringstream oss;

    for (auto face: this->faces)
    {
        for (int i = 0; i < 3; ++i)
        {
            auto vertexPosition = positions[face.pos[i]];
            auto normalPosition = normals[face.normal[i]];

            oss << "Position: [";
            oss << vertexPosition[0] << ',';
            oss << vertexPosition[1] << ',';
            oss << vertexPosition[2] << ']';

            oss << "\t Normals: [";
            oss << normalPosition[0] << ',';
            oss << normalPosition[1] << ',';
            oss << normalPosition[2] << ']';
            oss << std::endl;
        }
    }

    return oss.str();

}

void ObjModel::loadVertices()
{
    for (const auto &face: this->faces)
    {
        for (int i = 0; i < 3; ++i)
        {
            auto vertexPosition = this->positions[face.pos[i]];
            auto normalPosition = this->normals[face.normal[i]];
            vertices.push_back(tigl::Vertex::PN(vertexPosition, normalPosition));
        }
    }
}

std::vector<tigl::Vertex> ObjModel::GetVertices()
{
    return vertices;
}
