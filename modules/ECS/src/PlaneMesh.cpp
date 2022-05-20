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
    Vertex::PC(glm::vec3(-1, -1, 0), glm::vec4(1)),
    Vertex::PC(glm::vec3(1, -1, 0), glm::vec4(1)),
    Vertex::PC(glm::vec3(1, 1, 0), glm::vec4(1)),
    Vertex::PC(glm::vec3(-1, 1, 0), glm::vec4(1))
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
    tigl::shader->setColorMult(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    tigl::shader->enableColor(true);
    tigl::shader->enableColorMult(true);


    tigl::drawVertices(GL_QUADS, PlaneMesh::vertices);

    tigl::shader->enableColor(false);
    tigl::shader->enableColorMult(false);
}
