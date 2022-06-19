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

/**
 * @brief Transform component to move, rotate and scale everything that owns this Componet e.g. any and every GameObject
 */
class Transform : public Component
{
    glm::vec3 position{};
    glm::vec3 rotation{};
    glm::vec3 scale{};
public:
    explicit Transform(const glm::vec3 &position, const glm::vec3 &rotation = {0.0f, 0.0f, 0.0f}, const glm::vec3 &scale = {1.0f, 1.0f, 1.0f});

    Transform();

    [[nodiscard]] const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    [[nodiscard]] glm::vec3 getRotation() const;

    void setRotation(const glm::vec3 &rotation);

    [[nodiscard]] const glm::vec3 &getScale() const;

    void setScale(const glm::vec3 &scale);


};

