//
// Created by doguk on 5/24/2022.
//
#include "AIPrefab.h"
#include "statemachine/CombatState.h"
#include "statemachine/WalkState.h"

AIPrefab::AIPrefab(CharacterStats* characterStats)
{
    aiContext = new AIContext();
    aiContext->characterStats = characterStats;
    this->collider = new Collider(aiContext->characterStats->range);
}

void AIPrefab::onTriggerEnter(Collider* other)
{
    TagEnum result = other->getGameObject()->tagEnum;
    if(result == ENEMY) {
        auto* combatState = new CombatState(aiContext);
        auto* otherStats = other->getGameObject()->FindComponent<CharacterStats>();
        if(otherStats) {
            combatState->otherStats = otherStats;
            aiContext->switchState(combatState);
        }
    } else if(result == STATE) {
        auto* moveState = new WalkState(aiContext);
        aiContext->switchState(moveState);
    }
}
