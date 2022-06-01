//
// Created by doguk on 5/24/2022.
//

#include <iostream>
#include "statemachine/CombatState.h"

void CombatState::actionSwitched()
{
    context->lerpController->Move(glm::vec3(0, 0, 0),
                                  glm::vec3(0, 0, 0),
                                  0); //Moves character
    std::cout << "CombatAction switched!" << std::endl;

}

CombatState::CombatState(AIContext *context) : State(context)
{
}
