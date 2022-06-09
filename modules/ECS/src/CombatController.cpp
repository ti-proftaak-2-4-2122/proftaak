//
// Created by doguk on 5/24/2022.
//

#include "CombatController.h"
#include "GameTimer.h"
#include "Scene.h"
#include <iostream>

void CombatController::Damage()
{
    if(otherStats->health-yourStats->damage < 0) {
        Scene::getSingleton().RemoveGameObject(otherStats->getGameObject());
        StopCombat();
        std::cout << "Stopping combat" << std::endl;
        return;
    }
    otherStats->health -= yourStats->damage;
    std::cout << "Did Damage from: " << ToString(yourStats->type) << " to: " << ToString
    (otherStats->type) << " new amount: " << otherStats->health << std::endl;
}

void CombatController::StartCombat(CharacterStats* yourStats, CharacterStats* otherStats,
                                   LerpController* lerpController)
{
    this->yourStats = yourStats;
    this->otherStats = otherStats;
    this->maxTime = yourStats->attackSpeed;
    IsAttacking = true;
    this->lerpController = lerpController;
}


void CombatController::Update()
{
    currentTime += GameTimer::getDeltaTime();
    if(IsAttacking && currentTime >= maxTime) {
        Damage();
        currentTime = 0;
    }
}


CombatController::CombatController()
{
}

void CombatController::StopCombat()
{
    IsAttacking = false;
    hasFought = true;

    //Checkpoint naar volgende punt
//    if(isTowerDestroyed){
//        this->lerpController->Move();
//    }
//    this->lerpController->Move();

}



