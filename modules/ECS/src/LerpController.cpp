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
    float deltaZ = endPos.z-startPos.z;
    float deltaX = endPos.x-startPos.x;

//    slope = glm::vec3(1,0, deltaZ/deltaX);
    //std::cout << "startPos: " << glm::to_string(startPos) << "endPos: " << glm::to_string(endPos) << "slope: " << glm::to_string(slope);
    auto targetPos = glm::lerp(startPos, endPos, 0.97f);
    gameObject->transform.setPosition((targetPos));
}


void LerpController::Update()
{
    Component::Update();

    if (CheckPos(gameObject->transform.getPosition(), endPos)) return;

//    gameObject->transform.setPosition((gameObject->transform.getPosition() + (this->slope *
//    GameTimer::getDeltaTime() * speedMult)));

//    fraction += GameTimer::getDeltaTime() * 0.5f;
}

LerpController::LerpController()
{
    slope = glm::vec3(0, 0, 0);
}

bool LerpController::CheckPos(glm::vec3 currentPos, glm::vec3 resultPos) const
{
    auto distance = glm::length(resultPos - currentPos);
    return distance <= roundValue;
}
