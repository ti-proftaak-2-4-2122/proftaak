//
// Created by doguk on 5/24/2022.
//

#include "statemachine/CombatState.h"

void CombatState::actionSwitched()
{
    context->lerpController->Move(glm::vec3(0, 0, 0),
                                  glm::vec3(0, 0, 0),
                                  0); //Moves character

}

CombatState::CombatState(AIContext *context) : State(context)
{
}
