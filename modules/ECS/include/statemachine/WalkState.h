//
// Created by doguk on 5/24/2022.
//

#pragma once
#include "statemachine/State.h"

class State;

class WalkState: public State
{
public:
    WalkState(AIContext& context);
    void actionSwitched() override;
};
