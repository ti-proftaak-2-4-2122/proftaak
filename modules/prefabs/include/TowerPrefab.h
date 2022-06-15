//
// Created by doguk on 5/27/2022.
//

#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "CharacterStats.h"
#include "CombatController.h"
#include "Mesh.h"
#include "gui/StrGuiComponent.h"

class GameObject;

class TowerPrefab : public GameObject
{
private:

    bool IsAttacking = false;
    float currentTime;

    Collider* collider;
    CharacterStats* characterStats;
    CharacterStats* otherStats;
    StrGuiComponent *strGuiComponent;

    void StartCombat(CharacterStats* otherStats);
    void StopCombat();
    void DoDamage();

public:
    explicit TowerPrefab(Transform *transform);

    void onTriggerEnter(Collider* other) override;

    void Update() override;


};


