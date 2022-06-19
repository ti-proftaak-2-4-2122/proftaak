/**
 * @file
 * @brief Header file for the CharacterStats struct
 * @author Daan van Donk
 * @date 24-05-2022
 */

#ifndef PROFTAAK24_CHARACTERSTATS_H
#define PROFTAAK24_CHARACTERSTATS_H

#include <utility>

#include "UnitTypeEnum.h"

/**
 * @brief Data class for storing stats of units and towers
 */
struct CharacterStats : public Component
{
    std::string name;
    float range;
    float health;
    float damage;
    float moveSpeed;
    float attackSpeed;
    UnitTypeEnum type;
    short team = -1; // this should only be set on 0(left), 1(right) or -1(uninitialized)

    CharacterStats(std::string name, float range, float health, float damage, float moveSpeed, float attackSpeed,
                   UnitTypeEnum typeEnum)
    : name(std::move(name)),
    range(range),
    health(health),
    damage(damage),
    moveSpeed
    (moveSpeed),
    attackSpeed
    (attackSpeed),
    type(typeEnum) {}
};
#endif //PROFTAAK24_CHARACTERSTATS_H
