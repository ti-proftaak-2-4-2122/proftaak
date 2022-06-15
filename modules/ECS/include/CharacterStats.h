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
    : name(name),
    range(range),
    health(health),
    damage(damage),
    moveSpeed
    (moveSpeed),
    attackSpeed
    (attackSpeed),
    type(typeEnum) {}

    void TakeDamage(const float& damageTaken)
    {
        this->health -= damageTaken;
    }
};
#endif //PROFTAAK24_CHARACTERSTATS_H
