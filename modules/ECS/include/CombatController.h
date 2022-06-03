//
// Created by doguk on 5/24/2022.
//
#pragma once
#include "Component.h"
#include "CharacterStats.h"

class Component;

struct CombatStats {
    float health;
    float damage;
    float attackSpeed;
};

class CombatController : public Component
{
private:
    void Damage();
    CombatStats yourStats;
    CombatStats otherStats;
    float currentTime;
    float maxTime;
public:
    bool IsAttacking = false;
    bool hasFought = false;

    void StartCombat(float yourDamage, float yourHealth, float yourAttackspeed, float
    otherDamage, float otherHealth, float otherAttackspeed);
    void StopCombat();
    void Update() override;

    CombatController(GameObject &gameObject);
};
