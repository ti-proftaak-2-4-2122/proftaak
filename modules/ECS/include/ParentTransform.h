//
// Created by twanh on 20-5-2022.
//

#pragma once

#include "Component.h"
#include "glm/glm.hpp"

class GameObject;
class Transform;

class ParentTransform : public Component
{
private:
    GameObject* parent;
public:
    ParentTransform(GameObject* parent);

    inline Transform& GetParentTransform();
    glm::mat4 GetParentModelMatrix();
};
