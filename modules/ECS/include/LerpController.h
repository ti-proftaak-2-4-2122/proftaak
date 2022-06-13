//
// Created by Daan van Donk on 11/05/2022.
//

#pragma once

#include "Component.h"
#include "glm/glm.hpp"

class GameObject;

class Component;

class LerpController : public Component
{
public:
    void Move(glm::vec3 startPos, glm::vec3 endPos, float speed);

    void Update() override;

    LerpController();

    bool CheckPos(glm::vec3 currentPos, glm::vec3 resultPos) const;
private:
    glm::vec3 slope{};
    glm::vec3 endPos;
    glm::vec3 startPos;
    float fraction = 0.0f;
    const float roundValue = 1.0f;
    const float speedMult = 10.0f;
};