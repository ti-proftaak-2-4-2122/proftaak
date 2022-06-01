//
// Created by Daan van Donk on 24/05/2022.
//

#pragma once

#include "Component.h"
#include "glm/glm.hpp"
#include <vector>
class Collider : public Component
{
private:
    bool hasEntered = true;
    inline static std::vector<Collider*> otherColliders;
public:
    float radius;

    Collider(float radius);
    void CheckCollision(Collider* other);

    void Update() override;

    static void CleanUp(Collider* collider);

    static void addCollider(Collider* collider);
};
