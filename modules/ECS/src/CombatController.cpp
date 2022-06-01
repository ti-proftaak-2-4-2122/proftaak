//
// Created by doguk on 5/24/2022.
//

#include "CombatController.h"

void CombatController::Damage(CharacterStats &yourStats, CharacterStats &otherStats)
{
    otherStats.health -= yourStats.damage;
    std::cout << "Player did damage done to tower, remaining health: " << otherStats.health <<"\n";
}
