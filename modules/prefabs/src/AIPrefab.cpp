//
// Created by doguk on 5/24/2022.
//
#include "AIPrefab.h"
#include "statemachine/CombatState.h"
#include "Transform.h"
#include "statemachine/WalkState.h"
#include "ModelManager.h"
#include <iostream>

AIPrefab::AIPrefab(Transform* transform, CharacterStats* characterStats) : GameObject(transform)
{
    LerpController* lerpController = new LerpController();
    AddComponent(lerpController);
    CombatController* combatController = new CombatController();
    AddComponent(combatController);
    Mesh* renderMesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));
    AddComponent(renderMesh);
    AddComponent(characterStats);

    Collider* collider = new Collider(characterStats->range);

    this->collider = collider;
    AddComponent(collider);

    AIContext* aiContext = new AIContext(*lerpController, *combatController, *characterStats);
    this->aiContext = aiContext;
    AddComponent(aiContext);
}

void AIPrefab::onTriggerEnter(Collider *other)
{
    GameObject::onTriggerEnter(other);

    CharacterStats* otherStats = other->getGameObject()->FindComponent<CharacterStats>();

    if(otherStats){
        aiContext->switchState((State *)new CombatState(*aiContext, *otherStats));
    }
}

void AIPrefab::onTriggerExit(Collider *other)
{
    GameObject::onTriggerExit(other);

    aiContext->switchState((State *)new WalkState(*aiContext));
}


