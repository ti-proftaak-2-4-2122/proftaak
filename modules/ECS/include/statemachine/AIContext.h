/**
 * @file
 * @brief Header file for the AIContext class
 * @author doguk
 * @date 20-05-2022
 */
#pragma once

#include "Component.h"
#include "State.h"
#include "LerpController.h"
#include "CombatController.h"

class Component;
class State;

class AIContext : public Component
{
public:
    LerpController *lerpController;
    CombatController *combatController;

    AIContext();

    State *currentState;

    void switchState(State *newState);
};