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

AIContext::AIContext()
{

}

void AIContext::Awake()
{
    currentState = new WalkState(this);
}


