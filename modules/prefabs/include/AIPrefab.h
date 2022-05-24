//
// Created by doguk on 5/24/2022.
//
#pragma once

#include "statemachine/AIContext.h"
#include "GameObject.h"
#include "Collider.h"
#include "CharacterStats.h"

class CombatState;

class AIPrefab : public GameObject
{
private:
    AIContext *aiContext;
    CharacterStats* characterStats;
    CombatController* combatController;
    Collider* collider;
public:
    AIPrefab(CharacterStats* characterStats);

    void onTriggerEnter(Collider* collider) override;
};
