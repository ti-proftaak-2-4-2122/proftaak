//
// Created by Daan van Donk on 12/05/2022.
//

#include "Mesh.h"
#include "tigl.h"
#include "ObjModel.h"

void Mesh::Draw()
{
    tigl::shader->setModelMatrix(glm::mat4(1.0f));
    tigl::begin(GL_TRIANGLES);

    for (const auto &item: objModel->GetVertices())
    {
        tigl::addVertex(item);
    }

    tigl::end();

}

Mesh::Mesh(ObjModel *_objmodel) : objModel(_objmodel) {}
