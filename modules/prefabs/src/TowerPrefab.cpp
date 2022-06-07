#include "TowerPrefab.h"
#include "ModelManager.h"
#include <iostream>

TowerPrefab::TowerPrefab(Transform& transform) : GameObject
(transform)
{
    CharacterStats* towerstats = new CharacterStats{*this, 8.0f, 5.0f, 5.0f, 0.0f, 1.0f,TOWER};
    this->characterStats = towerstats;
    this->combatController = new CombatController(*this);
    std::cout << "Constructor call for tower" << std::endl;
    this->collider = new Collider(*this, characterStats->range);
    Mesh* mesh = new Mesh(*this, ModelManager::getModel("../resource/models/tower.obj"));
    mesh->SetDiffuseColor({0.619, 0, 0.537});
    AddComponent(*mesh);
    AddComponent(*this->collider);
    AddComponent(*this->combatController);
    AddComponent(*this->characterStats);
}

void TowerPrefab::onTriggerEnter(Collider *other)
{
    std::cout << "On Trigger Enter for tower" << std::endl;
    GameObject::onTriggerEnter(other);
//    CharacterStats& otherStats = other->getGameObject().FindComponent<CharacterStats>();
//
//    if(otherStats) {
//        combatController->StartCombat(this->characterStats, otherStats);
//        std::cout << "The character got damaged, his health is: " << otherStats.health <<
//        std::endl;
//    }
}

void TowerPrefab::Update()
{
    GameObject::Update();
}

