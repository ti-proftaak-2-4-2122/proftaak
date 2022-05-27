//
// Created by Daan van Donk on 24/05/2022.
//

#pragma once

#include "Component.h"
#include "glm/glm.hpp"
class Collider : public Component
{

public:
    Collider(float radius, glm::vec3 position);
    void CheckCollision(Collider* other);
    float radius;
    glm::vec3 position;
};
