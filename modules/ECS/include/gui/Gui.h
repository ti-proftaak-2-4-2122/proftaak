//
// Created by Ewout on 1-6-2022.
//

#pragma once

#include "Component.h"
#include "GuiComponent.h"
#include "glad/glad.h"
#include "glm/ext/matrix_transform.hpp"
#include "GuiComponent.h"

class GameObject;

class Gui : public Component
{
private:
    GLuint fontTxId;
    std::vector<GuiComponent *> guiComponents;

public:
    void Draw() override;

    void AddGuiComponent(GuiComponent *);

    void RemoveGuiComponent(GuiComponent *);

    Gui();
};