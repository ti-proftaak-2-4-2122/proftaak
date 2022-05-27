//
// Created by doguk on 5/24/2022.
//

#include "statemachine/WalkState.h"
#include "glm/glm.hpp"
#include <iostream>
#include "Transform.h"

void WalkState::actionSwitched()
{
    std::cout << "Walkstate Action switched!" << std::endl;
    glm::vec3 pos = context->getGameObject()->transform.getPosition();
    context->lerpController->Move(pos,glm::vec3(7.0f, pos.y, pos.z), context->characterStats
            ->moveSpeed);
}

WalkState::WalkState(AIContext *aiContext) : State(aiContext)
{

}
