//
// Created by doguk on 5/27/2022.
//

#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "CharacterStats.h"
#include "CombatController.h"
#include "Mesh.h"

class GameObject;

class TowerPrefab : public GameObject
{
private:
    Collider* collider;
    CombatController* combatController;
    CharacterStats* characterStats;
public:
    TowerPrefab(Transform *transform, CharacterStats *characterStats);

    void onTriggerEnter(Collider* other) override;

    void Update() override;
};


