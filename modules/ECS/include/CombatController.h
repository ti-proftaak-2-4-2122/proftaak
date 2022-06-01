//
// Created by doguk on 5/24/2022.
//
#pragma once
#include "Component.h"
#include "CharacterStats.h"

class Component;

class CombatController : public Component
{
public:
    void Damage(CharacterStats& yourStats,  CharacterStats& otherStats);
};
