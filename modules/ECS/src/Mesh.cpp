//
// Created by Daan van Donk on 12/05/2022.
//

#include "Mesh.h"
#include "tigl.h"

void Mesh::DrawMesh() {
    {
        tigl::shader->setModelMatrix(glm::mat4(1.0f));
        tigl::begin(GL_TRIANGLES);

        for(auto face : objModel->faces) {
            for (int i = 0; i < 3; ++i)
            {
                auto vertexPosition = objModel->positions[face.pos[i]];
                auto normalPosition = objModel->normals[face.normal[i]];
                tigl::addVertex(tigl::Vertex::PN(vertexPosition, normalPosition));
            }
        }

        tigl::end();
    }
}