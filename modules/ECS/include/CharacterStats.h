//
// Created by robin on 20-May-22.
//

#pragma once

#include "Component.h"

class Component;

class GameObject;

typedef enum {
    AIR,
    GROUND,
    VEHICLE
} CharacterType;

class CharacterStats : public Component
{
public:


    CharacterType characterType;

    //Health
    float health;

    //Movement
    float moveSpeed;

    //Attack


    CharacterType AttackTarget;
    float AttackDamage;
    float attackSpeed;
    float attackRange;

    CharacterStats( CharacterType characterType = GROUND,
                    float health = 100.0f,
                    float moveSpeed = 2.0f,
                    CharacterType attackTarget = VEHICLE,
                    float attackDamage = 5.0f,
                    float attackSpeed = 3.0f,
                    float attackRange = 50.0f        );
};
