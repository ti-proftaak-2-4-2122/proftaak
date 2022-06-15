#include "TowerPrefab.h"
#include "ModelManager.h"
#include "GameTimer.h"
#include "Scene.h"
#include <iostream>
#include "Mesh.h"

#include "glm/glm.hpp"
#include "../../../colours.h"

TowerPrefab::TowerPrefab(Transform *transform, std::string name) : GameObject(transform)
{
    this->characterStats = new CharacterStats{name, 4.f, 100.0f, 10.0f, 0.0f, 1.5f, TOWER};
    this->collider = new Collider(this->characterStats->range);
     this->strGuiComponent = new StrGuiComponent("");
     this->strGuiComponent->setScale({0.7f, 0.7f, 0.7f});

     InitTowerTeam();

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
    GameObject::onTriggerEnter(other);
    auto *oCharacterStats = other->getGameObject()->FindComponent<CharacterStats>();

    if(oCharacterStats) {
        if((oCharacterStats->type == TOWER) && (this->characterStats->team == oCharacterStats->team)) return;
        StartCombat(oCharacterStats);
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
    if (currentTime >= this->characterStats->attackSpeed)
    {
        otherStats->TakeDamage(this->characterStats->damage);
        currentTime = 0;
    }
    if (otherStats->health <= 0)
    {
        StopCombat();
    }
}

void TowerPrefab::InitTowerTeam()
{
    if(this->transform.getPosition().x <= 0)
    {
        this->characterStats->team = 0;
    }
    else
    {
        this->characterStats->team = 1;
    }
}
