/**
 * @file
 * @brief Header file for the CharacterStats struct
 * @author Daan van Donk
 * @date 24-05-2022
 */

#ifndef PROFTAAK24_CHARACTERSTATS_H
#define PROFTAAK24_CHARACTERSTATS_H

#include "UnitTypeEnum.h"

struct CharacterStats : public Component
{
    float range;
    float health;
    float damage;
    float moveSpeed;
    float attackSpeed;
    UnitTypeEnum type;
    short team = -1; // this should only be set on 0(left), 1(right) or -1(uninitialized)

    CharacterStats(float range, float health, float damage, float moveSpeed, float attackSpeed,
                   UnitTypeEnum typeEnum)
    : range(range),
    health(health),
    damage(damage),
    moveSpeed
    (moveSpeed),
    attackSpeed
    (attackSpeed),
    type(typeEnum) {}
};
#endif //PROFTAAK24_CHARACTERSTATS_H
