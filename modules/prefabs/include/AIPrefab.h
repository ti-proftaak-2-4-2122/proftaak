/**
 * @file
 * @brief Header file for the AIPrefab class
 * @author doguk
 * @date 24-05-2022
 */
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
