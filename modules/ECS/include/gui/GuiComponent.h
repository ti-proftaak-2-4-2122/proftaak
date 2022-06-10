//
// Created by Ewout on 10-6-2022.
//

#pragma once

#include "glm/detail/type_vec3.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/vec3.hpp"

class GuiComponent
{

protected:
    glm::vec3 position;
    glm::vec3 scale;
public:
    GuiComponent(const glm::vec3 &position, const glm::vec3 &scale);

    virtual void draw();
};
