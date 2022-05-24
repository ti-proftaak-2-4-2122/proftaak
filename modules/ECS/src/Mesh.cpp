//
// Created by Daan van Donk on 12/05/2022.
//

#include "Mesh.h"

void Mesh::Draw()
{
    auto transform = gameObject->transform;

    auto modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::scale(modelMatrix, transform.getScale());

    modelMatrix = glm::translate(modelMatrix, transform.getPosition());

    auto rotation = transform.getRotation();
    modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));

    tigl::shader->setModelMatrix(modelMatrix);
    tigl::shader->setLightDiffuse(0, diffuseColor);
    tigl::drawVertices(GL_TRIANGLES, objModel->GetVertices());
}

Mesh::Mesh(ObjModel *_objmodel) : objModel(_objmodel) {}

void Mesh::SetColor(const glm::vec4& color)
{
    for(auto &vertex : objModel->GetVertices())
        vertex.color = color;

}

void Mesh::SetDiffuseColor(const glm::vec3& color)
{
    this->diffuseColor = color;
}
