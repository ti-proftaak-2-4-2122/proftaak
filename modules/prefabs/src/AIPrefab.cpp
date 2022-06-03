//
// Created by doguk on 5/24/2022.
//
#include "AIPrefab.h"
#include "Transform.h"
#include "ModelManager.h"

#include <iostream>

AIPrefab::AIPrefab(Transform* transform, CharacterStats* characterStats) : GameObject(transform)
{
    this->lerpController = new LerpController();
    AddComponent(lerpController);

    this->combatController = new CombatController();
    AddComponent(combatController);

    Mesh* renderMesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));
    AddComponent(renderMesh);

    this->characterStats = characterStats;
    AddComponent(this->characterStats);

    this->collider = new Collider(characterStats->range);
    AddComponent(collider);

    lerpController->Move(this->transform.getPosition(), checkPoints[0],
                         characterStats->moveSpeed);
}

void AIPrefab::onTriggerEnter(Collider *other)
{
    GameObject::onTriggerEnter(other);

    CharacterStats* otherStats = other->getGameObject()->FindComponent<CharacterStats>();

    if(otherStats){
        combatController->StartCombat(this->characterStats, otherStats);
    }

}

void AIPrefab::onTriggerExit(Collider *other)
{
    GameObject::onTriggerExit(other);
}

void AIPrefab::Update()
{
    GameObject::Update();

    //TODO Not call every update
    if(!combatController->IsAttacking && combatController->hasFought && !test) {

        test = true;
        std::cout << " Testing new walk" << std::endl;
                  lerpController->Move(this->transform.getPosition(), checkPoints[2],
                                       characterStats->moveSpeed);
    }
}


