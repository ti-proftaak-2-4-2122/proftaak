//
// Created by Daan van Donk on 12/05/2022.
//

#ifndef PROFTAAK24_MESH_H
#define PROFTAAK24_MESH_H

#include <vector>
#include "glm/glm.hpp"
#include "Component.h"


class ObjModel;
class GameObject;

class Mesh : public Component
{
private:
    ObjModel* objModel;
public:

    Mesh(ObjModel* _objmodel, GameObject* gameObject);

    void DrawMesh();
};


#endif //PROFTAAK24_MESH_H
