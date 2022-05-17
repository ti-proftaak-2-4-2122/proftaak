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
#include "glm/gtc/matrix_transform.hpp"


class Mesh : public Component
{
private:
    ObjModel* objModel;
public:

    Mesh(ObjModel* _objmodel) {
        objModel = _objmodel;
    }

    void DrawMesh();
};


#endif //PROFTAAK24_MESH_H
