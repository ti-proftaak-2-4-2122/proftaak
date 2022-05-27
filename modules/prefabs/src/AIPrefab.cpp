//
// Created by doguk on 5/24/2022.
//
#include "AIPrefab.h"
#include "statemachine/CombatState.h"
#include "statemachine/WalkState.h"
#include "glm/glm.hpp"
#include "Transform.h"
#include "ModelManager.h"

AIPrefab::AIPrefab(Transform *transform, CharacterStats *characterStats) : GameObject(transform)
{
    aiContext = new AIContext();
    aiContext->characterStats = characterStats;
    LerpController* _lerpController = new LerpController();
    aiContext->lerpController = _lerpController;
    this->collider = new Collider(characterStats->range);
    AddComponent(aiContext);
    AddComponent(this->collider);
    AddComponent(new Mesh(ModelManager::getModel("../resource/models/box.obj")));
    AddComponent(_lerpController);
    aiContext->Awake();
    aiContext->switchState(new WalkState(aiContext));
}

void AIPrefab::onTriggerEnter(Collider* collider)
{
    TagEnum result = collider->getGameObject()->tagEnum;
    if(result == ENEMY) {
        auto* combatState = new CombatState(aiContext);
        auto* otherStats = collider->getGameObject()->FindComponent<CharacterStats>();
        if(otherStats) {
            combatState->otherStats = otherStats;
            aiContext->switchState(combatState);
        }
    } else if(result == STATE) {
        auto* moveState = new WalkState(aiContext);
        aiContext->switchState(moveState);
    }
}
