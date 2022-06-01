/**
 * @file
 * @brief Header file for the ParentTransform class
 * @author twanh
 * @date 20-05-2022
 */

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

