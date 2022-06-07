//
// Created by doguk on 5/24/2022.
//
#include "AIPrefab.h"
#include "Transform.h"
#include "ModelManager.h"
#include "Mesh.h"
#include "glm/glm.hpp"
#include <iostream>

AIPrefab::AIPrefab(Transform& transform) : GameObject(transform)
{
    this->lerpController = new LerpController(*this);
    AddComponent(*lerpController);

    CharacterStats* characterStats = new CharacterStats{*this, 4.0f, 100.0f, 5.0f, 2.0f,2.0f, LAND};
    AddComponent(*characterStats);
    Mesh* renderMesh = new Mesh(*this,ModelManager::getModel("../resource/models/box.obj"));
    AddComponent(*renderMesh);

    this->characterStats = characterStats;
    AddComponent(*this->characterStats);

    this->collider = new Collider(*this, characterStats->range);
    AddComponent(*collider);

    lerpController->Move(this->transform.getPosition(), glm::vec3(25.0f, 0.0f, -12.0f),
                         characterStats->moveSpeed);
}

void AIPrefab::onTriggerEnter(Collider *other)
{
    GameObject::onTriggerEnter(other);

    lerpController->Move(this->transform.getPosition(), glm::vec3(50.0f, 0.0f, 0.0f),
                         characterStats->moveSpeed);
//    CharacterStats& otherStats = other->getGameObject().FindComponent<CharacterStats>();
//
//    this->combatController = new CombatController(*this, this->characterStats, otherStats);
//    AddComponent(combatController);
//    if(otherStats){
//        combatController->StartCombat(this->characterStats, otherStats);
//    }

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


