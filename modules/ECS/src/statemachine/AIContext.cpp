//
// Created by doguk on 5/20/2022.
//

#include "statemachine/AIContext.h"
#include "statemachine/WalkState.h"

void AIContext::switchState(State* newState)
{
    this->currentState = newState;
}

AIContext::AIContext()
{
    currentState = new WalkState(this);
    this->lerpController = new LerpController();
}


