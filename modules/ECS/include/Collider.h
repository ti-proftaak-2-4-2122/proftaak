//
// Created by Daan van Donk on 24/05/2022.
//

#pragma once

#include "Component.h"
#include "glm/glm.hpp"
class Collider : public Component
{
private:
    bool hasEntered = true;
public:
    float radius;
    std::vector<Collider*> otherColliders;
    Collider(float radius);
    void CheckCollision(Collider* other);

    void Update() override;
};
