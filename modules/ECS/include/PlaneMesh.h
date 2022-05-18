//
// Created by twanh on 18-5-2022.
//

#pragma once

#include <tigl.h>

#include "Component.h"

using tigl::Vertex;

class PlaneMesh : public Component
{
private:
    static const std::vector<Vertex> vertices;

public:
    PlaneMesh();

    void Draw() override;
};
