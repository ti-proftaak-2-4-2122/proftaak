//
// Created by doguk on 5/24/2022.
//
#pragma once

#include "statemachine/AIContext.h"
#include "GameObject.h"

class CombatState;

class AIPrefab : public GameObject
{
private:
    AIContext *aiContext;
public:
    AIPrefab();

    void onTriggerEnter(Collider* collider) override;
};
