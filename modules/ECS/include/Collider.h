//
// Created by Daan van Donk on 24/05/2022.
//

#pragma once

#include "Component.h"
#include "glm/glm.hpp"
class Collider : public Component
{
public:
    float radius;
    glm::vec3 position;
    std::vector<Collider*> otherColliders;
    Collider(float radius, glm::vec3 position);
    void CheckCollision(Collider* other);

    void Update() override;
};
