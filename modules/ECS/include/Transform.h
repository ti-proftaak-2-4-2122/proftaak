//
// Created by Daan van Donk on 10/05/2022.
//

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
    Transform(GameObject &gameObject, const glm::vec3 &position,
              const glm::vec3 &rotation, const glm::vec3 &scale);

    Transform(GameObject &gameObject);

    [[nodiscard]] const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    [[nodiscard]] const glm::vec3 &getRotation() const;

    void setRotation(const glm::vec3 &rotation);

    [[nodiscard]] const glm::vec3 &getScale() const;

    void setScale(const glm::vec3 &scale);


};

