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
    std::cout << "Going to move" << std::endl;
    //Reset lerp
    stepCount = 0;
    //Calculate 3D slope
    slope = glm::vec3(speed / (endPos.x - startPos.x), speed / (endPos.y - startPos.y),
                      speed / (endPos
                                       .z - startPos.z));

    for (int i = 0; i < 3; ++i)
    {
        if (std::isinf(slope[i]))
        {
            this->slope[i] = 0;
        }
    }
    // startPos*speed + endPos*(1.f-speed);
    //Calculate how many ticks is needed to complete to full move
    stepAmount = (int) ((endPos.x - startPos.x) / slope.x);
}


void LerpController::Update()
{
    Component::Update();

    if (stepCount >= stepAmount) return;
    //Move the gameobject
    //TODO implement delta time
    gameObject->transform.setPosition((gameObject->transform.getPosition() + this->slope ));
    stepCount++;

}

LerpController::LerpController()
{
    slope = glm::vec3(0, 0, 0);
    stepAmount = 0;
    stepCount = 0;
}
