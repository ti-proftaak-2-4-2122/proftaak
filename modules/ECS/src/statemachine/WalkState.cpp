//
// Created by doguk on 5/24/2022.
//

#include "statemachine/WalkState.h"
#include "glm/glm.hpp"
#include <iostream>

void WalkState::actionSwitched()
{
//    context->lerpController->Move(glm::vec3(0,0,0),
//                             glm::vec3(0,0,0),
//                             0); //Moves character
    std::cout << "Walkstate Action switched!" << std::endl;
}

WalkState::WalkState(AIContext *aiContext) : State(aiContext)
{
}
