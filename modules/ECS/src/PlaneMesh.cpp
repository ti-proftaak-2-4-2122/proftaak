//
// Created by twanh on 18-5-2022.
//

#include <vector>

#include <tigl.h>
#include <glm/glm.hpp>

#include "PlaneMesh.h"

using tigl::Vertex;

const std::vector<Vertex> PlaneMesh::vertices = std::vector<Vertex>({
    Vertex::PT(glm::vec3(-1, -1, 0), glm::vec2(0, 1)),
    Vertex::PT(glm::vec3(1, -1, 0), glm::vec2(1, 1)),
    Vertex::PT(glm::vec3(1, 1, 0), glm::vec2(1, 0)),
    Vertex::PT(glm::vec3(-1, 1, 0), glm::vec2(0, 0))
});

PlaneMesh::PlaneMesh()
{
}

void PlaneMesh::Draw()
{
    glm::mat4 modelMatrix(1.0f);

    tigl::shader->setModelMatrix(modelMatrix);

    tigl::drawVertices(GL_QUADS, PlaneMesh::vertices);
}
