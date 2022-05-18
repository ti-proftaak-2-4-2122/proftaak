//
// Created by Daan van Donk on 12/05/2022.
//

#include "Mesh.h"
#include "tigl.h"
#include "ObjModel.h"
#include "Transform.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

void Mesh::Draw()
{
    auto transform = (Transform *) gameObject->getTransform();


    auto modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::scale(modelMatrix,transform->scale);

    modelMatrix = glm::translate(modelMatrix, transform->position);

    auto rotation = transform->rotation;
    modelMatrix = glm::rotate(modelMatrix,rotation.x,glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix,rotation.y,glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix,rotation.z,glm::vec3(0, 0, 1));

    tigl::shader->setModelMatrix(modelMatrix);


    tigl::begin(GL_TRIANGLES);

    for (const auto &item: objModel->GetVertices())
    {
        tigl::addVertex(item);
    }

    tigl::end();

}

Mesh::Mesh(ObjModel *_objmodel) : objModel(_objmodel) {}
