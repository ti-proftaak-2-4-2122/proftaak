/**
 * @file
 * @brief Source file for the CombatController class
 * @author doguk
 * @date 24-05-2022
 */

#include "CombatController.h"

void CombatController::Damage(CharacterStats &yourStats, CharacterStats &otherStats)
{
    otherStats.health -= yourStats.damage;
}
