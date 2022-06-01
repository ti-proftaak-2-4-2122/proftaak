//
// Created by doguk on 5/24/2022.
//
#include "AIPrefab.h"
#include "statemachine/CombatState.h"

AIPrefab::AIPrefab()
{
    aiContext = new AIContext();
}

void AIPrefab::onTriggerEnter(Collider* collider)
{
    auto* combatState = new CombatState(aiContext);
    aiContext->switchState(combatState);
}
