//
// Created by Ewout on 10-6-2022.
//

#pragma once

#include "GuiComponent.h"
#include <string>

class StrGuiComponent : public GuiComponent
{
private:
    static void DrawChar(glm::mat4 &modelMatrix, char characteristic);

    std::string text;

public:
    void draw() override;
    StrGuiComponent(const glm::vec3 &position, const glm::vec3 &scale, const std::string &text);

};



