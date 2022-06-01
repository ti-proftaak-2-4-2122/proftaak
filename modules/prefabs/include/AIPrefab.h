//
// Created by doguk on 5/24/2022.
//
#pragma once

#include "GameObject.h"
#include "Collider.h"
#include "CharacterStats.h"
#include "Mesh.h"
#include "LerpController.h"
#include "CombatController.h"

class CombatState;

class AIPrefab : public GameObject
{
private:
    LerpController* lerpController;
    CombatController* combatController;
    Collider* collider;
    CharacterStats* characterStats;
public:
    AIPrefab(Transform* transform, CharacterStats* characterStats);

    void onTriggerEnter(Collider* other) override;
    void onTriggerExit(Collider* other) override;
};
