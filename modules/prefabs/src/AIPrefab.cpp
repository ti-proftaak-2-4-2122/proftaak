/**
 * @file
 * @brief Source file for the AIPrefab class
 * @author doguk
 * @date 24-05-2022
 */
#include "AIPrefab.h"
#include "Transform.h"
#include "ModelManager.h"
#include "GameTimer.h"
#include "Scene.h"
#include "gui/StrGuiComponent.h"
#include "../../../colours.h"
#include "TowerPrefab.h"

#include <iostream>

AIPrefab::AIPrefab(Transform *transform, UnitTypeEnum type) : GameObject(transform)
{
    this->lerpController = new LerpController();
    AddComponent(lerpController);

    Mesh *renderMesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));
    renderMesh->SetColor(TEAL_TURKISH);
    AddComponent(renderMesh);

    InitStats(type);
    InitCheckpoints();
    AddComponent(this->characterStats);

    this->strGuiComponent = new StrGuiComponent("");
    this->strGuiComponent->setScale({0.5f, 0.5f, 0.5f});

    this->collider = new Collider(this->characterStats->range);
    AddComponent(collider);
    AddComponent(this->strGuiComponent);

    lerpController->Move(this->transform.getPosition(), checkPoints[0],
                         characterStats->moveSpeed);
}

void AIPrefab::onTriggerEnter(Collider *other)
{
    GameObject::onTriggerEnter(other);

    lerpController->Move(this->transform.getPosition(), this->transform.getPosition(),characterStats->moveSpeed);
    otherStats = other->getGameObject()->FindComponent<CharacterStats>();

    if (otherStats && (this->characterStats->team != otherStats->team))
    {
        std::cout << "Starting combat with tower: " << otherStats->name << std::endl;

        //Start combat
        StartCombat(otherStats);
    }

}

void AIPrefab::onTriggerExit(Collider *other)
{
    GameObject::onTriggerExit(other);
}

void AIPrefab::Update()
{
    GameObject::Update();
    char buffer[15];
    snprintf(buffer, 15, "Health: %.2f", this->characterStats->health);
    this->strGuiComponent->setText(buffer);
    this->strGuiComponent->setPosition({this->transform.getPosition().x-10,
                                        this->transform.getPosition().y,
                                        this->transform.getPosition().z-3});

    if (this->IsAttacking) DoDamage();

    if(this->isLerpINTR) return;

    if (this->wayPointIndex >= this->checkPoints.size())
    {
        this->lerpController->Move(this->transform.getPosition(), this->transform.getPosition(), this->characterStats->moveSpeed);
        return;
    }


    if (this->lerpController->CheckPos(this->transform.getPosition(), this->checkPoints[wayPointIndex]))
    {
        std::cout << "doing the lerpy derp " << '\n';
        this->wayPointIndex++;
        this->lerpController->Move(this->transform.getPosition(), this->checkPoints[wayPointIndex], this->characterStats->moveSpeed);
    }
}

void AIPrefab::StartCombat(CharacterStats *otherStats2)
{
    this->currentTime = this->characterStats->attackSpeed;
    this->otherStats = otherStats2;
    this->IsAttacking = true;
    this->isLerpINTR = true;
}

void AIPrefab::DoDamage()
{
    currentTime += GameTimer::getDeltaTime();
    if (IsAttacking && (currentTime >= this->characterStats->attackSpeed))
    {
        otherStats->TakeDamage(this->characterStats->damage);
        currentTime = 0;
    }
    if (otherStats->health <= 0)
    {
        std::cout << "Enemy: " << otherStats->name << " Has 0 Hp" << std::endl;
        Scene::getSingleton().RemoveGameObject(otherStats->getGameObject());
        StopCombat();
    }
}

void AIPrefab::StopCombat()
{
    this->isLerpINTR = false;
    IsAttacking = false;
}

void AIPrefab::InitStats(UnitTypeEnum type)
{
    switch (type)
    {
        case FAST:
            this->characterStats = new CharacterStats{"FAST prefab",2.f, 100.0f, 3.0f, 0.5f, 0.5f, LAND};
            break;
        case SLOW:
            this->characterStats = new CharacterStats{"SLOW prefab",4.f, 100.0f, 10.0f, 0.2f, 1.f, LAND};
            break;
        case LAND:
            this->characterStats = new CharacterStats{"LAND prefab",2.5f, 100.0f, 10.0f, 0.5f, 1.0f, LAND};
            break;
        default:
            this->characterStats = new CharacterStats{"Default LAND unit",2.5f, 100.0f, 10.0f, 0.5f, 1.0f, LAND};
            break;
    }
}

void AIPrefab::InitCheckpoints()
{
    glm::vec3 pos = this->transform.getPosition();

    if (pos.x <= 0 && pos.z <= 0)
    {
        //links boven
        std::cout << "linksboven\n";
        this->checkPoints.push_back(this->predefinedPositions[TOP_LEFT_BRIDGE]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_TOP_RIGHT]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_BOTTOM_RIGHT]);
        this->characterStats->team = 0;
    } else if (pos.x <= 0 && pos.z > 0)
    {
        // links onder spawnen
        std::cout << "linksonder\n";
        this->checkPoints.push_back(this->predefinedPositions[BOTTOM_LEFT_BRIDGE]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_BOTTOM_RIGHT]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_TOP_RIGHT]);
        this->characterStats->team = 0;
    } else if (pos.x > 0 && pos.z <= 0)
    {
        //Rechts boven
        std::cout << "rechtsboven\n";
        this->checkPoints.push_back(this->predefinedPositions[TOP_RIGHT_BRIDGE]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_TOP_LEFT]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_BOTTOM_LEFT]);
        this->characterStats->team = 1;
    }else if (pos.x > 0 && pos.z > 0)
    {
        //Rechts onder
        std::cout << "rechtsonder\n";
        this->checkPoints.push_back(this->predefinedPositions[BOTTOM_RIGHT_BRIDGE]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_BOTTOM_LEFT]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_TOP_LEFT]);
        this->characterStats->team = 1;
    }
}

bool AIPrefab::setLerpINTR(const bool& newLerpINTR)
{
    return this->isLerpINTR = newLerpINTR;
}

