//
// Created by Daan van Donk on 11/05/2022.
//

#include <iostream>
#include "LerpController.h"
#include "Transform.h"
#include "glm/vec3.hpp"
#include "GameTimer.h"

void LerpController::Move(glm::vec3 startPos, glm::vec3 endPos, float speed)
{
    this->endPos = endPos;

    std::cout << "Going to move" << std::endl;

    float deltaZ = endPos.z-startPos.z;
    float deltaX = endPos.x-startPos.x;

    slope = glm::vec3(1,0, deltaZ/ deltaX);
}


void LerpController::Update()
{
    Component::Update();

    if (CheckPos(gameObject.transform.getPosition(), endPos)) return;

    gameObject.transform.setPosition((gameObject.transform.getPosition() + (this->slope *
    GameTimer::getDeltaTime() * speedMult)));

}

LerpController::LerpController(GameObject &gameObject) : Component(gameObject)
{
    slope = glm::vec3(0, 0, 0);
}

bool LerpController::CheckPos(glm::vec3 currentPos, glm::vec3 resultPos) const
{
    auto distance = glm::length(resultPos - currentPos);
    return distance <= roundValue;
}
