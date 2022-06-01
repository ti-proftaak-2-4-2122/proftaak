//
// Created by doguk on 5/24/2022.
//
#include "AIPrefab.h"
#include "Transform.h"
#include "ModelManager.h"

#include <iostream>

AIPrefab::AIPrefab(const Transform &AItransform, CharacterStats *characterStats) : GameObject()
{
    this->transform.setPosition(AItransform.getPosition());
    this->transform.setRotation(AItransform.getRotation());
    this->transform.setScale(AItransform.getRotation());


    this->lerpController = new LerpController();
    AddComponent(lerpController);

    this->combatController = new CombatController();
    AddComponent(combatController);

    Mesh *renderMesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));
    AddComponent(renderMesh);

    this->characterStats = characterStats;
    AddComponent(this->characterStats);

    this->collider = new Collider(characterStats->range);
    AddComponent(collider);

    lerpController->Move(this->transform.getPosition(), glm::vec3(5.5f, 9.0f, 1.0f),
                         characterStats->moveSpeed);
}

void AIPrefab::onTriggerEnter(Collider *other)
{
    GameObject::onTriggerEnter(other);

    CharacterStats *otherStats = other->getGameObject()->FindComponent<CharacterStats>();

    if (otherStats)
    {
        combatController->StartCombat(this->characterStats, otherStats);
    }
}

void AIPrefab::onTriggerExit(Collider *other)
{
    GameObject::onTriggerExit(other);
}


