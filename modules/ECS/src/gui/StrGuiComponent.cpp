//
// Created by Ewout on 10-6-2022.
//

#include <string>
#include <utility>
#include "tigl.h"


#include "glm/vec3.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "gui/StrGuiComponent.h"

#include "Transform.h"
#include "gui/Gui.h"

#define ATLAS_WIDTH 10
#define ATLAS_HEIGHT 10

void StrGuiComponent::DrawChar(glm::mat4 &modelMatrix, char characteristic)
{
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.0f, 0.0f));
    tigl::shader->setModelMatrix(modelMatrix);

    auto textureIndex = characteristic - 32;

    const float textureWidth = 1.0f / ATLAS_WIDTH;
    const float textureHeigth = 1.0f / ATLAS_HEIGHT;

    const float tx0 = (float) (textureIndex % ATLAS_WIDTH) * textureWidth;
    const float tx1 = tx0 + textureWidth;
    const float ty0 = (textureIndex / ATLAS_HEIGHT) * textureHeigth;
    const float ty1 = ty0 + textureHeigth;

    tigl::begin(GL_QUADS);
    tigl::addVertex(tigl::Vertex::PT(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(tx0, ty1)));
    tigl::addVertex(tigl::Vertex::PT(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(tx1, ty1)));
    tigl::addVertex(tigl::Vertex::PT(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(tx1, ty0)));
    tigl::addVertex(tigl::Vertex::PT(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(tx0, ty0)));
    tigl::end();
}

void StrGuiComponent::Draw()
{
    auto *gui = dynamic_cast<Gui *>(gameObject);
    glDisable(GL_CULL_FACE);
    tigl::shader->setProjectionMatrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 200.0f));
    tigl::shader->setViewMatrix(glm::lookAt(
            glm::vec3(0.0f, 0, 5),
            glm::vec3(0.0f, 0, 0),
            glm::vec3(0.0f, 1, 0)
    ));


    glBindTexture(GL_TEXTURE_2D, gui->fontTxId);

    tigl::shader->enableAlphaTest(true);
    tigl::shader->enableTexture(true);

    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.075f, 0.075f, 0.075f) * scale);

    for (char &c: text)
    {
        DrawChar(modelMatrix, c);
    }

    tigl::shader->enableAlphaTest(false);
    tigl::shader->enableTexture(false);

    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}


StrGuiComponent::StrGuiComponent(std::string text, const glm::vec3 &position, const
glm::vec3 &scale) : text(std::move(text)), position(position), scale(scale)
{

}

void StrGuiComponent::setPosition(const glm::vec3 &newPosition)
{
    StrGuiComponent::position = newPosition;
}


