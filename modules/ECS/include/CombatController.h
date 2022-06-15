/**
 * @file
 * @brief Header file for the CombatController class
 * @author doguk
 * @date 24-05-2022
 */

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

    float currentTime = 0.0f;
    float maxTime = 0.0f;
    bool isTowerDestroyed = false;
    CharacterStats* yourStats = nullptr;
    CharacterStats* otherStats = nullptr;
    LerpController* lerpController = nullptr;

public:
    bool IsAttacking = false;
    bool hasFought = false;

    void StartCombat(CharacterStats* characterStats, CharacterStats* pCharacterStats, LerpController* lerpController);
    void Update() override;

    CombatController();
};
