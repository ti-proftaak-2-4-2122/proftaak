//
// Created by doguk on 5/20/2022.
//
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
    CharacterStats* characterStats;

    AIContext();

    State *currentState;

    void switchState(State *newState);

    void Awake() override;
};