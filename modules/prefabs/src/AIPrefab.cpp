/**
 * @file
 * @brief Source file for the AIPrefab class
 * @author doguk
 * @date 24-05-2022
 */
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
