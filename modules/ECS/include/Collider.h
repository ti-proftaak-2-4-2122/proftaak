/**
 * @file
 * @brief Header file for the Collider class
 * @author Daan van Donk
 * @date 24-05-2022
 */

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
