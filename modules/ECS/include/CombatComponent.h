//
// Created by robin on 20-May-22.
//


#pragma once

#include "Component.h"

class Component;

class GameObject;

class CombatComponent : public Component
{
public:
    void Attack(GameObject* attack, GameObject* enemy);
    void update();
};


