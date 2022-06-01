/**
 * @file
 * @brief Header file for the Collider class
 * @author Daan van Donk
 * @date 24-05-2022
 */

#pragma once

#include "Component.h"
#include "glm/glm.hpp"
class Collider : public Component
{
private:
    bool hasEntered;
public:
    float radius;
    glm::vec3 position;
    std::vector<Collider*> otherColliders;
    Collider(float radius, glm::vec3 position);
    void CheckCollision(Collider* other);

    void Update() override;
};
