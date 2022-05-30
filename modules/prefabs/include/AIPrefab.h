//
// Created by doguk on 5/24/2022.
//
#pragma once

#include "statemachine/AIContext.h"
#include "GameObject.h"
#include "Collider.h"
#include "CharacterStats.h"
#include "Mesh.h"

class CombatState;

class AIPrefab : public GameObject
{
private:
    AIContext* aiContext;
    Collider* collider;
public:
    AIPrefab(Transform* transform, CharacterStats* characterStats);

    void onTriggerEnter(Collider* other) override;
    void onTriggerExit(Collider* other) override;
};
