#include "TowerPrefab.h"
#include "ModelManager.h"
#include "GameTimer.h"
#include "Scene.h"
#include <iostream>
#include "Mesh.h"
#include "glm/glm.hpp"
#include "gui/StrGuiComponent.h"

TowerPrefab::TowerPrefab(Transform *transform) : GameObject
                                                         (transform)
{
    std::cout << "Constructor call for tower" << std::endl;
    this->characterStats = new CharacterStats{4.0f, 5.0f, 5.0f, 0.0f, 1.0f, TOWER};
    this->collider = new Collider(this->characterStats->range);
    this->strGuiComponent = new StrGuiComponent("Ik lik pik");


    Mesh *mesh = new Mesh(ModelManager::getModel("../resource/models/tower.obj"));
    mesh->SetDiffuseColor({0.619, 0, 0.537});
    AddComponent(mesh);
    AddComponent(this->collider);
    AddComponent(this->characterStats);
    AddComponent(this->strGuiComponent);
    //strGuiComponent->setPosition( glm::vec2(0.0f,0.5f));

    //strGuiComponent->setPosition(transform->getPosition());
}

void TowerPrefab::onTriggerEnter(Collider *other)
{
    std::cout << "On Trigger Enter for tower" << std::endl;
    GameObject::onTriggerEnter(other);
    CharacterStats *otherStats = other->getGameObject()->FindComponent<CharacterStats>();

    if (otherStats)
    {
        StartCombat(otherStats);
        std::cout << "The character got damaged, his health is: " << otherStats->health <<
                  std::endl;
    }
}

void TowerPrefab::Update()
{
    GameObject::Update();

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

