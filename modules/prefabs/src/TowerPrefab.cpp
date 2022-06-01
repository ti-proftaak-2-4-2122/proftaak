#include "TowerPrefab.h"
#include "ModelManager.h"
#include <iostream>

TowerPrefab::TowerPrefab(Transform *transform, CharacterStats *characterStats) : GameObject
(transform), characterStats(characterStats)
{
    std::cout << "Constructor call for tower" << std::endl;
    this->combatController = new CombatController();
    this->collider = new Collider(characterStats->range);
    AddComponent(new Mesh(ModelManager::getModel("../resource/models/tower.obj")));
    AddComponent(this->collider);
    AddComponent(this->combatController);
    AddComponent(this->characterStats);
}

void TowerPrefab::onTriggerEnter(Collider *other)
{
    std::cout << "On Trigger Enter for tower" << std::endl;
    GameObject::onTriggerEnter(other);
    CharacterStats* otherStats = other->getGameObject()->FindComponent<CharacterStats>();

    if(otherStats) {
        combatController->StartCombat(this->characterStats, otherStats);
        std::cout << "The character got damaged, his health is: " << otherStats->health <<
        std::endl;
    }
}

void TowerPrefab::Update()
{
    GameObject::Update();
}

