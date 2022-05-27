//
// Created by Daan van Donk on 12/05/2022.
//

#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "Component.h"


class ObjModel;

class GameObject;

class Mesh : public Component
{
private:
    ObjModel *objModel;
public:

    explicit Mesh(ObjModel *_objmodel);

    void Draw() override;
};