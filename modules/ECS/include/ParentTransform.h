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

/**
 * @class Component used for positioning a GameObject relative to its parent
 */
class ParentTransform : public Component
{
private:
    GameObject* parent;

public:
    /**
     * @brief Default constructor, requires a reference to a parent GameObject
     * @param parent Reference to the parent GameObject used for positioning
     */
    ParentTransform(GameObject* parent);

    /**
     * @brief Gets the transform component of the parent
     * @return The parent transform
     */
    inline Transform& GetParentTransform();

    /**
     * @brief Gets the calculated model matrix of the parent, based on it's current transform
     * @return The parent model matrix
     */
    glm::mat4 GetParentModelMatrix();
};

