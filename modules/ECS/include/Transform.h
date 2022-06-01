//
// Created by Daan van Donk on 10/05/2022.
//

/**
 * @file
 * @brief Header file for the Transform class
 * @author Daan van Donk
 * @date 10-05-2022
 */
#pragma once

#include "Component.h"
#include "glm/glm.hpp"

class GameObject;

class Transform : public Component
{
    glm::vec3 position{};
    glm::vec3 rotation{};
    glm::vec3 scale{};
public:
    [[nodiscard]] const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    [[nodiscard]] const glm::vec3 &getRotation() const;

    void setRotation(const glm::vec3 &rotation);

    [[nodiscard]] const glm::vec3 &getScale() const;

    void setScale(const glm::vec3 &scale);

    Transform();
};

