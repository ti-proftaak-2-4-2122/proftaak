//
// Created by Ewout on 10-6-2022.
//

#include <string>
#include "gui/StrGuiComponent.h"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "tigl.h"

#define ATLAS_WIDTH 10
#define ATLAS_HEIGHT 10

StrGuiComponent::StrGuiComponent(
        const glm::vec3 &position, const glm::vec3 &scale,
        const std::string &textString) : GuiComponent(position,
                                                      scale)
{
    text = textString;
}


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

void StrGuiComponent::draw()
{
    auto modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.075f, 0.075f, 0.075f)*scale);

    for (char &c: text)
    {
        DrawChar(modelMatrix, c);
    }


}
