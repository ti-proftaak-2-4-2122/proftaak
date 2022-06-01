//
// Created by doguk on 5/24/2022.
//

#include "CombatController.h"
#include "GameTimer.h"
#include "Scene.h"

void CombatController::Damage()
{
    if(otherStats->health-yourStats->damage < 0) {
        Scene::getSingleton().RemoveGameObject(otherStats->getGameObject());
        StopCombat();
        return;
    }
    otherStats->health -= yourStats->damage;
    std::cout << "Did Damage from: " << ToString(yourStats->type) << " to: " << ToString
    (otherStats->type) << " new amount: " << otherStats->health << std::endl;
}

void CombatController::StartCombat(CharacterStats* yourStats, CharacterStats* otherStats)
{
    this->yourStats = yourStats;
    this->otherStats = otherStats;
    this->maxTime = yourStats->attackSpeed;
    IsAttacking = true;
}


void CombatController::Update()
{
    Component::Update();

    currentTime += GameTimer::deltatime;
    if(IsAttacking && currentTime >= maxTime) {
        Damage();
        currentTime = 0;
    }
}

void CombatController::StopCombat()
{
    IsAttacking = false;
}

CombatController::CombatController()
{
}



