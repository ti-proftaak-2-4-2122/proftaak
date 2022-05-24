//
// Created by robin on 20-May-22.
//

#pragma once

#include "glm/glm.hpp"
#include "Component.h"
#include "CharacterStats.h"

class Component;

class GameObject;

class Collider : public Component
{
private:
    float radius;

    bool CheckCollision(Collider &other);

public:

    void CheckColliders(const std::vector<Collider *> &other);

    Collider(float radius);
};



