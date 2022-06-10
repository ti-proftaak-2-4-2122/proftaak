/**
 * @file
 * @brief Source file for the AIContext class
 * @author doguk
 * @date 05-05-2022
 */

#include "statemachine/AIContext.h"
#include "statemachine/WalkState.h"

void AIContext::switchState(State* newState)
{
    this->currentState = newState;
    this->currentState->actionSwitched();
}

AIContext::AIContext()
{
    currentState = new WalkState(this);
    this->lerpController = new LerpController();
}


