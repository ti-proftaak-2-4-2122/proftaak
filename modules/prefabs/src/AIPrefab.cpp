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
#include "../../../colours.h"

#include <iostream>

AIPrefab::AIPrefab(Transform *transform, UnitTypeEnum type) : GameObject(transform)
{
    this->lerpController = new LerpController();
    AddComponent(lerpController);

    Mesh *renderMesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));
    renderMesh->SetColor(TEAL_TURKISH);
    AddComponent(renderMesh);

    InitStats(type);
    AddComponent(this->characterStats);

    this->collider = new Collider(this->characterStats->range);
    AddComponent(collider);

    InitCheckpoints();

    lerpController->Move(this->transform.getPosition(), checkPoints[0],
                         characterStats->moveSpeed);
}

void AIPrefab::onTriggerEnter(Collider *other)
{
    GameObject::onTriggerEnter(other);

    glm::vec3 pos = this->transform.getPosition();

    Transform transform1 = this->transform;
    transform1.setPosition(glm::vec3(pos.x + 1, pos.y, pos.z));
    //lerpController->Move(this->transform.getPosition(), transform1.getPosition() ,characterStats->moveSpeed);
    otherStats = other->getGameObject()->FindComponent<CharacterStats>();

    if (otherStats)
    {
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
    if (IsAttacking) DoDamage();
    if (wayPointIndex >= checkPoints.size())
    {
        lerpController->Move(this->transform.getPosition(), this->transform.getPosition(), characterStats->moveSpeed);
        return;
    }
    if (lerpController->CheckPos(this->transform.getPosition(), checkPoints[wayPointIndex]))
    {

        wayPointIndex++;
        std::cout << "waypointindex: " << wayPointIndex << " to point: " << checkPoints[wayPointIndex].x << "," << checkPoints[wayPointIndex].z <<
                  std::endl;
        lerpController->Move(this->transform.getPosition(), checkPoints[wayPointIndex], characterStats->moveSpeed);
    }
}

void AIPrefab::StartCombat(CharacterStats *otherStats2)
{
    this->otherStats = otherStats2;
    this->IsAttacking = true;
}

void AIPrefab::DoDamage()
{
    currentTime += GameTimer::getDeltaTime();
    if (IsAttacking && currentTime >= this->characterStats->attackSpeed)
    {
        otherStats->health -= this->characterStats->damage;
        //std::cout << "New Health: " << otherStats->health << std::endl;
        currentTime = 0;
    }
    if (otherStats->health <= 0)
    {
        if (otherStats->type == TOWER)
        {
            IsTowerDestroyed = true;
        }

        Scene::getSingleton().RemoveGameObject(otherStats->getGameObject());
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

void AIPrefab::InitStats(UnitTypeEnum type)
{

    //std::cout << "Init stats: " << ToString(type) << std::endl;
    switch (type)
    {
        case FAST:
            this->characterStats = new CharacterStats{2.0f, 100.0f, 5.0f, 0.5f, 3.0f, LAND};
            break;
        case SLOW:
            this->characterStats = new CharacterStats{2.0f, 100.0f, 10.0f, 0.5f, 1.0f, LAND};
            break;
        case LAND:
            this->characterStats = new CharacterStats{2.0f, 100.0f, 10.0f, 0.5f, 1.0f, LAND};
            break;
        default:
            this->characterStats = new CharacterStats{2.0f, 100.0f, 10.0f, 0.5f, 1.0f, LAND};
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
    } else if (pos.x > 0 && pos.z > 0)
    {
        //Rechts onder
        std::cout << "rechtsonder\n";
        this->checkPoints.push_back(this->predefinedPositions[BOTTOM_RIGHT_BRIDGE]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_BOTTOM_LEFT]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_TOP_LEFT]);
        this->characterStats->team = 1;
    }
}


