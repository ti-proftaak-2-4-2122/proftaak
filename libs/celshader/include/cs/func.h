//
// Created by twanh on 9-6-2022.
//

#pragma once

#include "cs/CelShader.h"

#include "tigl.h"

using tigl::Vertex;
using tigl::VBO;

namespace cs
{
    void init();

    void begin(GLenum shape);

    void addVertex(const Vertex& vertex);

    void end();

    void drawVertices(GLenum shape, const std::vector<Vertex> &vertices);

    VBO* createVbo(const std::vector<Vertex>& vertices);

    void drawVertices(GLenum shape, VBO* vbo);
}