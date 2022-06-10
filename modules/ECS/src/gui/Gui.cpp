//
// Created by Ewout on 1-6-2022.
//

#include "gui/Gui.h"
#include "tigl.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Transform.h"
#include <TextureLoader.h>


void Gui::Draw()
{
    tigl::shader->enableAlphaTest(true);

    glDisable(GL_CULL_FACE);
    tigl::shader->setProjectionMatrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 200.0f));
    tigl::shader->setViewMatrix(glm::lookAt(
            glm::vec3(0.0f, 0, 5),
            glm::vec3(0.0f, 0, 0),
            glm::vec3(0.0f, 1, 0)
    ));

    glBindTexture(GL_TEXTURE_2D, fontTxId);
    tigl::shader->enableTexture(true);

    for (const auto &guiComponent: guiComponents)
    {
        guiComponent->draw();
    }

    tigl::shader->enableAlphaTest(false);
    tigl::shader->enableTexture(false);

    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}

Gui::Gui()
{
    fontTxId = textureLoader::getTexture("../resource/textures/Courier.png");
}

void Gui::AddGuiComponent(GuiComponent *guiComponent)
{
    auto found = std::find(guiComponents.begin(), guiComponents.end(), guiComponent);

    if (found == guiComponents.end())
        guiComponents.push_back(guiComponent);
}

void Gui::RemoveGuiComponent(GuiComponent *guiComponent)
{
    auto found = std::find(guiComponents.begin(), guiComponents.end(), guiComponent);

    if (found != guiComponents.end())
        guiComponents.erase(found);
}

