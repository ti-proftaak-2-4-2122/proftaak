//
// Created by Daan van Donk on 12/05/2022.
//

#ifndef PROFTAAK24_MESH_H
#define PROFTAAK24_MESH_H

#include <vector>
#include "glm/vec3.hpp"
#include "glad/glad.h"
#include "Component.h"
#include "ObjModel.h"
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

class Mesh : public Component
{
public:
    ObjModel objModel;
    Mesh(std::string objPath) {
        objModel = ObjModel(objPath);
    }

    void DrawMesh() {
        glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float width = 1400;
        float height = 800;

        tigl::shader->setProjectionMatrix(
                glm::perspective(glm::radians(70.0f), width / height, 0.1f, 200.0f));
        tigl::shader->setViewMatrix(
                glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
        tigl::shader->setModelMatrix(glm::mat4(1.0f));
        tigl::begin(GL_TRIANGLES);

        for(auto vertex : objModel.positions) {
            tigl::addVertex(tigl::Vertex::P(vertex));
        }

        tigl::end();
    }
private:
};


#endif //PROFTAAK24_MESH_H
