/**
 * @file
 * @brief Source file for the CombatController class
 * @author doguk
 * @date 24-05-2022
 */

#include "CombatController.h"
#include "GameTimer.h"
#include "Scene.h"
#include <iostream>

void CombatController::Damage()
{
    if (otherStats->health - yourStats->damage < 0)
    {
        Scene::getSingleton().RemoveGameObject(otherStats->getGameObject());
        StopCombat();
        std::cout << "Stopping combat" << std::endl;
        return;
    }
    otherStats->health -= yourStats->damage;
    std::cout << "Did Damage from: " << ToString(yourStats->type) << " to: " << ToString
            (otherStats->type) << " new amount: " << otherStats->health << std::endl;
}

void CombatController::StartCombat(CharacterStats *yCharacterStats, CharacterStats *oCharacterStats,
                                   LerpController *nlerpController)
{
    this->yourStats = yCharacterStats;
    this->otherStats = oCharacterStats;
    this->maxTime = yCharacterStats->attackSpeed;
    IsAttacking = true;
    this->lerpController = nlerpController;
}


void CombatController::Update()
{
    currentTime += GameTimer::getDeltaTime();
    if (IsAttacking && currentTime >= maxTime)
    {
        Damage();
        currentTime = 0;
    }
}


CombatController::CombatController()
= default;

void CombatController::StopCombat()
{
    IsAttacking = false;

    //Checkpoint naar volgende punt
//    if(isTowerDestroyed){
//        this->lerpController->Move();
//    }
//    this->lerpController->Move();

}



