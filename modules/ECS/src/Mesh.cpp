/**
 * @file
 * @brief Source file for the Mesh class
 * @author Daan van Donk
 * @date 12-05-2022
 */

#include "Mesh.h"
#include "tigl.h"
#include "ObjModel.h"
#include "Transform.h"
#include "ParentTransform.h"
#include "cs/func.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <iostream>

void Mesh::Awake() {
    this->parentTransform = this->gameObject->FindComponent<ParentTransform>();
}

void Mesh::Draw()
{
    auto transform = this->gameObject->transform;

    auto modelMatrix = this->parentTransform == nullptr ?
            glm::mat4(1.0f)
            : parentTransform->GetParentModelMatrix();

    modelMatrix = glm::scale(modelMatrix, transform.getScale());

    modelMatrix = glm::translate(modelMatrix, transform.getPosition());

    auto rotation = transform.getRotation();
    modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0, 0, 1));

    cs::shader->use();

    cs::shader->setModelMatrix(modelMatrix);
    cs::shader->setColorMult(this->color);

    cs::drawVertices(GL_TRIANGLES, this->objModel->GetVertices());

}

Mesh::Mesh(ObjModel *_objmodel) : objModel(_objmodel) {}

void Mesh::SetColor(const glm::vec4& color)
{
    this->color = color;
}

void Mesh::SetAlpha(float alpha) {
    this->color.a = alpha;
}

void Mesh::SetMesh(ObjModel *model)
{
    objModel = model;
}