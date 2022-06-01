/**
 * @file
 * @brief Header file for the CombatController class
 * @author doguk
 * @date 24-05-2022
 */

#pragma once
#include "Component.h"
#include "CharacterStats.h"

class Component;

class CombatController : public Component
{
public:
    void Damage(CharacterStats& yourStats,  CharacterStats& otherStats);
};
