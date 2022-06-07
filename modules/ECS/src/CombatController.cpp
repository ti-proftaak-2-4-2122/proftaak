//
// Created by doguk on 5/24/2022.
//

#include "CombatController.h"
#include "GameTimer.h"
#include "Scene.h"
#include <iostream>

void CombatController::Damage()
{
    if(otherStats.health-yourStats.damage < 0) {
//        Scene::getSingleton().RemoveGameObject(otherStats.getGameObject());
        StopCombat();
        std::cout << "Stopping combat" << std::endl;
        return;
    }
    otherStats.health -= yourStats.damage;
//    std::cout << "Did Damage from: " << ToString(yourStats.type) << " to: " << ToString
//    (otherStats->type) << " new amount: " << otherStats->health << std::endl;
}

void CombatController::StartCombat(float yourDamage, float yourHealth, float yourAttackspeed, float
otherDamage, float otherHealth, float otherAttackspeed)
{
    yourStats = {yourDamage, yourHealth,yourAttackspeed };
    otherStats = {otherDamage, otherHealth, otherAttackspeed};
    this->maxTime = yourStats.attackSpeed;
    IsAttacking = true;
}


void CombatController::Update()
{
    Component::Update();

    currentTime += GameTimer::getDeltaTime();
    if(IsAttacking && currentTime >= maxTime) {
        Damage();
        currentTime = 0;
    }
}


CombatController::CombatController(GameObject &gameObject) : Component(gameObject)
{
}

void CombatController::StopCombat()
{
    IsAttacking = false;
    hasFought = true;
}



