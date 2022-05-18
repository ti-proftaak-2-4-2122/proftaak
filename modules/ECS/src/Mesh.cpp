//
// Created by Daan van Donk on 12/05/2022.
//

#include "Mesh.h"
#include "tigl.h"
#include "ObjModel.h"
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

void Mesh::Draw()
{
    auto transform = (Transform *) gameObject->getTransform();


    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform->position);
    tigl::shader->setModelMatrix(modelMatrix);

    tigl::begin(GL_TRIANGLES);

    for (const auto &item: objModel->GetVertices())
    {
        tigl::addVertex(item);
    }

    tigl::end();

}

Mesh::Mesh(ObjModel *_objmodel) : objModel(_objmodel) {}
