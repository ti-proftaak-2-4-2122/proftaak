//
// Created by Daan van Donk on 24/05/2022.
//

#pragma once

#include "Component.h"

class Collider : public Component
{
    float radius;
public:
    Collider(float radius);
};
