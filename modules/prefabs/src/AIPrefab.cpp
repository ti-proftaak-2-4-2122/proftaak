//
// Created by doguk on 5/24/2022.
//
#include "AIPrefab.h"
#include "statemachine/CombatState.h"

AIPrefab::AIPrefab(CharacterStats* characterStats)
{
    aiContext = new AIContext();
    this->characterStats = characterStats;
    this->collider = new Collider(this->characterStats->range);

    combatController = new CombatController();
}

void AIPrefab::onTriggerEnter(Collider* other)
{
    TagEnum result = other->getGameObject()->tagEnum;
    if(result == ENEMY) {
        auto* otherStats = other->getGameObject()->FindComponent<CharacterStats>();
        if(otherStats) {
            combatController->Damage(*(this->characterStats), *otherStats);
        }
    } else if(result == STATE) {
        auto* combatState = new CombatState(aiContext);
        aiContext->switchState(combatState);
    }
}
