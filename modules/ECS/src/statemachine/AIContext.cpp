//
// Created by doguk on 5/20/2022.
//

#include "statemachine/AIContext.h"
#include "statemachine/WalkState.h"

void AIContext::switchState(State* newState)
{
    this->currentState = newState;
    this->currentState->actionSwitched();
}

void AIContext::Awake()
{
    currentState = (State*) new WalkState(*(this));
}

AIContext::AIContext(LerpController &lerpController, CombatController &combatController,
                     CharacterStats &characterStats) : lerpController(lerpController),
                     combatController(combatController), characterStats(characterStats)
{

}


