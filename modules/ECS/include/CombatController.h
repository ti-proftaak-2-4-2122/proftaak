//
// Created by doguk on 5/24/2022.
//
#pragma once
#include "Component.h"
#include "LerpController.h"
#include "CharacterStats.h"

class Component;

class CombatController : public Component
{
private:
    void StopCombat();
    void Damage();

    float currentTime;
    float maxTime;
    bool isTowerDestroyed = false;
    CharacterStats* yourStats;
    CharacterStats* otherStats;
    LerpController* lerpController;



public:
    bool IsAttacking = false;
    bool hasFought = false;

    void StartCombat(CharacterStats* yourStats, CharacterStats* otherStats, LerpController* lerpController);
    void Update() override;

    CombatController();
};
