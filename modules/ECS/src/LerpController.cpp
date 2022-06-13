//
// Created by Daan van Donk on 11/05/2022.
//

#include <iostream>
#include "LerpController.h"
#include "Transform.h"
#include "glm/vec3.hpp"
#include "GameTimer.h"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/compatibility.hpp"

void LerpController::Move(glm::vec3 startPos, glm::vec3 endPos, float speed)
{
    this->endPos = endPos;
    this->startPos = startPos;

    fraction = 0.0f;
}

void LerpController::Update()
{
    Component::Update();

    if (CheckPos(gameObject->transform.getPosition(), endPos)) return;

    auto targetPos = glm::lerp(startPos, endPos, fraction);
    gameObject->transform.setPosition((targetPos));

    fraction += GameTimer::getDeltaTime() * 0.5f;
}

LerpController::LerpController()
{
}

bool LerpController::CheckPos(glm::vec3 currentPos, glm::vec3 resultPos) const
{
    auto distance = glm::length(resultPos - currentPos);
    return distance <= roundValue;
}
