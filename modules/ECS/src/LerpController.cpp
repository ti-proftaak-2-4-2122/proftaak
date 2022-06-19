/**
 * @file
 * @brief Source file for the LerpController class
 * @author Daan van Donk
 * @date 11-05-2022
 */

#include <iostream>
#include "LerpController.h"
#include "Transform.h"
#include "glm/vec3.hpp"
#include "GameTimer.h"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/compatibility.hpp"

void LerpController::Move(glm::vec3 nStartPos, glm::vec3 nEndPos, float speed)
{
    this->endPos = nEndPos;
    this->startPos = nStartPos;

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
