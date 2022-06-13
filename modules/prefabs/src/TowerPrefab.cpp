#include "TowerPrefab.h"
#include "ModelManager.h"
#include "GameTimer.h"
#include "Scene.h"
#include <iostream>
#include "Mesh.h"
#include "gui/StrGuiComponent.h"

#include "glm/glm.hpp"
#include "../../../colours.h"

TowerPrefab::TowerPrefab(Transform *transform) : GameObject(transform)
{
    std::cout << "Constructor call for tower" << std::endl;
    this->characterStats = new CharacterStats{4.0f, 5.0f, 5.0f, 0.0f, 1.0f, TOWER};
    this->collider = new Collider(this->characterStats->range);
     this->strGuiComponent = new StrGuiComponent("");

     this->strGuiComponent->setPosition(transform->getPosition());
    Mesh* mesh = new Mesh(ModelManager::getModel("../resource/models/tower.obj"));
    mesh->SetColor(RED_BARRA);

    AddComponent(mesh);
    AddComponent(this->collider);
    AddComponent(this->characterStats);
    AddComponent(this->strGuiComponent);

}

void TowerPrefab::onTriggerEnter(Collider *other)
{
    std::cout << "On Trigger Enter for tower" << std::endl;
    GameObject::onTriggerEnter(other);
    auto *oCharacterStats = other->getGameObject()->FindComponent<CharacterStats>();

    if(oCharacterStats) {
        if(oCharacterStats->type == TOWER) return;
        StartCombat(oCharacterStats);
        std::cout << "The character got damaged, his health is: " << oCharacterStats->health << std::endl;
    }
}

void TowerPrefab::Update()
{
    GameObject::Update();
    char buffer[15];
    snprintf(buffer, 15, "Health: %.2f", characterStats->health);
    strGuiComponent->setText(buffer);

    if (!IsAttacking) return;
    DoDamage();
}

void TowerPrefab::StartCombat(CharacterStats *otherStats)
{
    this->otherStats = otherStats;
    this->IsAttacking = true;
}

void TowerPrefab::StopCombat()
{
    this->IsAttacking = false;
    Scene::getSingleton().RemoveGameObject(otherStats->getGameObject());
}

void TowerPrefab::DoDamage()
{
    currentTime += GameTimer::getDeltaTime();
    if (IsAttacking && currentTime >= this->characterStats->attackSpeed)
    {
        otherStats->health -= this->characterStats->damage;
        currentTime = 0;
    }
    if (otherStats->health <= 0)
    {
        StopCombat();
    }
}

