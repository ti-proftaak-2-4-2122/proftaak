//
// Created by Ewout on 1-6-2022.
//

#include "gui/Gui.h"
#include "tigl.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Transform.h"
#include <TextureLoader.h>
#include "TagEnum.h"
#include "gui/StrGuiComponent.h"


Gui::Gui()
{
    fontTxId = textureLoader::getTexture("../resource/textures/Courier.png");
    tagEnum = TagEnum::GUI;
}

void Gui::MouseButtonPress(double xPosition,double yPosition)
{
    auto* component = FindComponent<StrGuiComponent>();
   if (component == nullptr)
       return;

   auto testPosition = glm::vec3(xPosition,yPosition,0.0f);
   component->setPosition(testPosition);
}
