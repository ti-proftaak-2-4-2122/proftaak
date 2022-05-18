//
// Created by twanh on 18-5-2022.
//

#include <vector>

#include <tigl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "PlaneMesh.h"
#include "Transform.h"

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

    auto transform = (Transform *) this->gameObject->getTransform();

    modelMatrix = glm::translate(modelMatrix, transform->position);

    modelMatrix = glm::rotate(modelMatrix, transform->rotation.x, glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, transform->rotation.y, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, transform->rotation.z, glm::vec3(0, 0, 1));

    modelMatrix = glm::scale(modelMatrix, transform->scale);

    tigl::shader->setModelMatrix(modelMatrix);

    tigl::drawVertices(GL_QUADS, PlaneMesh::vertices);
}
