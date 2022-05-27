#include "TowerPrefab.h"
#include "ModelManager.h"
#include <iostream>

TowerPrefab::TowerPrefab(Transform *transform, CharacterStats *characterStats) : GameObject(transform)
{
    this->collider = new Collider(characterStats->range);
    this->combatController = new CombatController();
    this->characterStats = characterStats;
    AddComponent(new Mesh(ModelManager::getModel("../resource/models/tower.obj")));
    AddComponent(this->collider);
    AddComponent(this->combatController);
    AddComponent(characterStats);
}

void TowerPrefab::onTriggerEnter(Collider *collider)
{
    GameObject::onTriggerEnter(collider);
    CharacterStats* otherStats = collider->getGameObject()->FindComponent<CharacterStats>();

    if(otherStats) {
        combatController->Damage(*this->characterStats, *otherStats);
        std::cout << "The character got damaged, his health is: " << otherStats->health <<
        std::endl;
    }
}

void TowerPrefab::Update() {
    if(enemyIsNear) {
        //TODO Factor in attackSpeed and constantly update damage values see onTriggerEnter for
        // logic
    }
}
