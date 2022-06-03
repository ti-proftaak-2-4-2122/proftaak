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
    //Reset lerp
    //Calculate 3D slope

    float deltaZ = startPos.z-endPos.z;
    float deltaX = startPos.x-endPos.x;

    if(deltaZ == 0) deltaZ = 1;
    if(deltaX == 0) deltaX = 1;
    slope = glm::vec3(1,0, deltaZ/ deltaX);
}


void LerpController::Update()
{
    Component::Update();

    if (CheckPos(gameObject->transform.getPosition(), endPos)) return;

    gameObject->transform.setPosition((gameObject->transform.getPosition() + (this->slope *
    GameTimer::getDeltaTime() * speedMult)));

}

LerpController::LerpController()
{
    slope = glm::vec3(0, 0, 0);
}

bool LerpController::CheckPos(glm::vec3 currentPos, glm::vec3 resultPos)
{
    double distance = sqrt(pow(resultPos.x - currentPos.x, 2) +
                           pow(resultPos.y - currentPos.y, 2) +
                           pow(resultPos.z - currentPos.z, 2));

    return distance <= roundValue;
}
