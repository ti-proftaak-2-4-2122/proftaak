//
// Created by doguk on 5/24/2022.
//
#pragma once
#include "Component.h"
#include "CharacterStats.h"

class Component;

class CombatController : public Component
{
private:
    void Damage();

    float currentTime;
    float maxTime;
    CharacterStats* yourStats;
    CharacterStats* otherStats;
public:
    bool IsAttacking = false;
    bool hasFought = false;

    void StartCombat(CharacterStats* yourStats, CharacterStats* otherStats);
    void StopCombat();
    void Update() override;

    CombatController();
};
