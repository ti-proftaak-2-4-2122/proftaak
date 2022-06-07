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
    bool test = false;
    LerpController* lerpController;
    CombatController* combatController;
    Collider* collider;
    CharacterStats* characterStats;
    const std::vector<glm::vec3> checkPoints {glm::vec3(50.0f, 0.0f, 0), glm::vec3(25.0f, 0.0f, -12.0f)
                                              , glm::vec3(50.0f, 0.0f, 0)};
public:
    AIPrefab(Transform& transform);

    void onTriggerEnter(Collider* other) override;
    void onTriggerExit(Collider* other) override;
    void Update() override;
};
