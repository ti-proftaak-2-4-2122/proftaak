#include "TowerPrefab.h"
#include "ModelManager.h"
#include "GameTimer.h"
#include "Scene.h"
#include <iostream>
#include <utility>
#include "Mesh.h"

#include "glm/glm.hpp"
#include "../../../colours.h"

TowerPrefab::TowerPrefab(Transform *transform, std::string name) : GameObject(transform)
{
    this->characterStats = new CharacterStats{std::move(name), 7.f, 100.0f, 2.0f, 0.0f, 0.5f, TOWER};
    InitTowerTeam();

    AddComponent(this->characterStats);

    Mesh* mesh = new Mesh(ModelManager::getModel("../resource/models/tower.obj"));
    mesh->SetColor(RED_BARRA);
    AddComponent(mesh);

    this->collider = new Collider(this->characterStats->range);
    AddComponent(this->collider);

    this->strGuiComponent = new StrGuiComponent("");
    this->strGuiComponent->setScale({0.7f, 0.7f, 0.7f});
    this->strGuiComponent->setPosition(transform->getPosition());
    AddComponent(this->strGuiComponent);
}

void TowerPrefab::onTriggerEnter(Collider *other)
{
    std::cout << "Reached the ontrigenter of tower " << "\n";
    GameObject::onTriggerEnter(other);
//    auto* oCharacterStats = other->getGameObject()->FindComponent<CharacterStats>();

    this->otherStats = other->getGameObject()->FindComponent<CharacterStats>();

    if (this->otherStats && (this->characterStats->team != this->otherStats->team))
    {
        //Start combat
        StartCombat(this->otherStats);
    }
}

void TowerPrefab::onTriggerExit(Collider *other)
{
    GameObject::onTriggerExit(other);
}

void TowerPrefab::Update()
{
    GameObject::Update();
    char buffer[15];
    snprintf(buffer, 15, "Health: %.2f", characterStats->health);
    strGuiComponent->setText(buffer);

    if (IsAttacking) DoDamage();
}

void TowerPrefab::StartCombat(CharacterStats *otherStats)
{
    this->otherStats = otherStats;
    this->IsAttacking = true;
}

void TowerPrefab::StopCombat()
{
    this->currentTime = this->characterStats->attackSpeed;
    this->IsAttacking = false;
    Scene::getSingleton().RemoveGameObject(otherStats->getGameObject());
}

void TowerPrefab::DoDamage()
{
    std::cout << "Reaching do damage function" << "\n";
    currentTime += GameTimer::getDeltaTime();
    if (currentTime >= this->characterStats->attackSpeed)
    {
        otherStats->health -= this->characterStats->health;
        std::cout << "Name: " << otherStats->name << " Taking damage: " << otherStats->health << "\n";
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

TowerPrefab::~TowerPrefab()
{
    if(this->characterStats->team == 1)
    {
        Scene::getSingleton().team_2_towerDestroyed++;
        std::cout << "Team 2 tower destroyed " << Scene::getSingleton().team_2_towerDestroyed << std::endl;
    }
    else
    {
        Scene::getSingleton().team_1_towerDestroyed++;
        std::cout << "Team 1 tower destroyed " << Scene::getSingleton().team_1_towerDestroyed << std::endl;
    }
}

