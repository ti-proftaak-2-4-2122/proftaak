/**
 * @file
 * @brief Header file for the CombatState class
 * @author doguk
 * @date 24-05-2022
 */
#pragma once
#include "State.h"

class State;

class CombatState : public State
{
public:
    CombatState(AIContext *context);
    void actionSwitched() override;
};
