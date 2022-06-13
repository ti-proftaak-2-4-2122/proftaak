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

#include <iostream>

AIPrefab::AIPrefab(Transform *transform, UnitTypeEnum type, bool hasSpawnedTop) : GameObject(transform),
hasSpawnedTop(hasSpawnedTop)
{
    this->lerpController = new LerpController();
    AddComponent(lerpController);

    Mesh *renderMesh = new Mesh(ModelManager::getModel("../resource/models/box.obj"));
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
    lerpController->Move(this->transform.getPosition(), transform1.getPosition() ,characterStats->moveSpeed);
    CharacterStats *otherStats = other->getGameObject()->FindComponent<CharacterStats>();

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
    if(lerpController->CheckPos(this->transform.getPosition(), checkPoints[0])) {
        lerpController->Move(this->transform.getPosition(), checkPoints[1],
                             characterStats->moveSpeed);
    }
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

    std::cout << "Init stats: " << ToString(type) << std::endl;
    switch (type)
    {
        case FAST:
            this->characterStats = new CharacterStats {4.0f, 100.0f, 5.0f, 3.0f, 3.0f, FAST};
            break;
        case SLOW:
            this->characterStats = new CharacterStats {4.0f, 100.0f, 10.0f, 1.0f, 1.0f, SLOW};
            break;
        case LAND:
            this->characterStats = new CharacterStats {4.0f, 100.0f, 10.0f, 1.0f, 1.0f, LAND};
            break;
        default:
            this->characterStats = new CharacterStats {4.0f, 100.0f, 10.0f, 1.0f, 1.0f, LAND};
            break;
    }
}

void AIPrefab::InitCheckpoints()
{
    glm::vec3 pos = this->transform.getPosition();

    if(pos.x < 0 && pos.z < 0)
    {
        //links boven
        this->checkPoints.push_back(this->predefinedPositions[TOP_LEFT_BRIDGE]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_TOP_RIGHT]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_BOTTOM_RIGHT]);
    }
    else if(pos.x < 0 && pos.z > 0)
    {
        // links onder spawnen
        this->checkPoints.push_back(this->predefinedPositions[BOTTOM_LEFT_BRIDGE]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_BOTTOM_RIGHT]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_TOP_RIGHT]);
    }
    else if(pos.x > 0 && pos.z < 0)
    {
        //Rechts boven
        this->checkPoints.push_back(this->predefinedPositions[TOP_RIGHT_BRIDGE]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_TOP_LEFT]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_TOP_LEFT]);
    }
    else if(pos.x > 0 && pos.z > 0)
    {
        //Rechts onder
        this->checkPoints.push_back(this->predefinedPositions[BOTTOM_RIGHT_BRIDGE]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_BOTTOM_LEFT]);
        this->checkPoints.push_back(this->predefinedPositions[TOWER_TOP_RIGHT]);
    }
}


