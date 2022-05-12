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
            Face face;
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
}


std::string ObjModel::Face::toString()
{
    std::ostringstream oss;
    //Todo could be better

    oss << "Position: [";
    oss << pos[0] << ',';
    oss << pos[1] << ',';
    oss << pos[2] << ']';

    oss << "\t Normals: [";
    oss << normal[0] << ',';
    oss << normal[1] << ',';
    oss << normal[2] << ']';

    return oss.str();

}
