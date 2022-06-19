/**
 * @file
 * @brief Header file for the ObjModel class
 * @author Ewout
 */

#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "tigl.h"

/**
 * @class Data class for storing Objects that have been loaded from @ModelManager
 */
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

    explicit ObjModel(const std::string &fileName);

    std::vector<tigl::Vertex>& GetVertices();

    std::string toString();

    tigl::VBO *getVbo();

private:
    /**
     * @brief Loads all vertices from the @faces
     */
    void loadVertices();

    std::vector<tigl::Vertex> vertices;
    tigl::VBO* vbo;
};

