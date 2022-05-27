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
    bool CheckCollision(glm::vec3 position2, float radius2);
    float radius;
    glm::vec3 position;
};
