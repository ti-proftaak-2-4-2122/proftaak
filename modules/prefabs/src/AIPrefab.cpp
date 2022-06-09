//
// Created by doguk on 5/24/2022.
//
#include "AIPrefab.h"
#include "Transform.h"
#include "ModelManager.h"
#include "GameTimer.h"

#include <iostream>

AIPrefab::AIPrefab(Transform *transform) : GameObject(transform)
{
    this->lerpController = new LerpController();
    AddComponent(lerpController);

    Mesh *renderMesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));
    AddComponent(renderMesh);

    this->characterStats = new CharacterStats {4.0f, 100.0f, 5.0f, 2.0f, 2.0f, LAND};
    AddComponent(this->characterStats);

    this->collider = new Collider(this->characterStats->range);
    AddComponent(collider);

    lerpController->Move(this->transform.getPosition(), checkPoints[1],
                         characterStats->moveSpeed);
}

void AIPrefab::onTriggerEnter(Collider *other)
{
    GameObject::onTriggerEnter(other);

    lerpController->Move(this->transform.getPosition(), this->transform.getPosition(),
                         characterStats->moveSpeed);
    CharacterStats *otherStats = other->getGameObject()->FindComponent<CharacterStats>();

    if (otherStats)
    {
        //Start combat
        std::cout << "Starting combat" << std::endl;
        StartCombat(otherStats);
    } else {
        std::cout << "Other Stats are null" << std::endl;
    }

}

void AIPrefab::onTriggerExit(Collider *other)
{
    GameObject::onTriggerExit(other);
}

void AIPrefab::Update()
{
    GameObject::Update();

    if (!IsAttacking) return;
    else DoDamage();

}

void AIPrefab::StartCombat(CharacterStats *otherStats)
{
    this->otherStats = otherStats;
    this->IsAttacking = true;
}

void AIPrefab::DoDamage()
{
    currentTime += GameTimer::getDeltaTime();
    if (IsAttacking && currentTime >= this->characterStats->attackSpeed)
    {
        otherStats->health -= this->characterStats->damage;
        std::cout << "New Health: " << otherStats->health << std::endl;
        currentTime = 0;
    }
    if (otherStats->health <= 0)
    {
        if (otherStats->type == TOWER)
        {
            IsTowerDestroyed = true;
        }

        StopCombat();
    }
}

void AIPrefab::StopCombat()
{
    if (IsTowerDestroyed)
    {
        lerpController->Move(this->transform.getPosition(), checkPoints[2],
                             characterStats->moveSpeed);
    } else
    {
        lerpController->Move(this->transform.getPosition(), checkPoints[1],
                             characterStats->moveSpeed);
    }
    IsAttacking = false;

}


