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



Gui::Gui()
{
    fontTxId = textureLoader::getTexture("../resource/textures/Courier.png");
    tagEnum = TagEnum::GUI;
}