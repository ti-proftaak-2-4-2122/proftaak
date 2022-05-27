//
// Created by doguk on 5/24/2022.
//
#pragma once
#include "State.h"

class State;

class CombatState : public State
{
public:
    CombatState(AIContext *context);
    void actionSwitched() override;
};
