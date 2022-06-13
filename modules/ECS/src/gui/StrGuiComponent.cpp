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
#include "TextureLoader.h"
#include "glm/gtc/type_ptr.hpp"
#include "../../../../user-config.h"

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

void StrGuiComponent::UpdateAfterDraw()
{
    tigl::shader->use();
    glDisable(GL_CULL_FACE);
    tigl::shader->setProjectionMatrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 200.0f));
    tigl::shader->setViewMatrix(glm::lookAt(
            glm::vec3(0.0f, 0, 5),
            glm::vec3(0.0f, 0, 0),
            glm::vec3(0.0f, 1, 0)
    ));

    glBindTexture(GL_TEXTURE_2D, fontTxId);

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
    fontTxId = textureLoader::getTexture("../resource/textures/Courier.png");
}

void StrGuiComponent::setPosition(const glm::vec3 &newPosition)
{
    glm::mat4 model = CONFIG_MATRIX_VIEW;
    glm::mat4 projection = CONFIG_MATRIX_PROJECTION;
    glm::ivec4 viewport;
    glGetIntegerv(GL_VIEWPORT, glm::value_ptr(viewport));

    glm::vec3 projected = glm::project(newPosition, model, projection, viewport);

    int width = CONFIG_WINDOW_WIDTH;
    int height = CONFIG_WINDOW_HEIGTH;

    float xNormalized, yNormalized;
    xNormalized = ((float) (projected.x / (float) width) * 2.0f) - 1.0f;
    yNormalized = ((float) (projected.y / (float) height) * 2.0f) - 1.0f;

    StrGuiComponent::position = glm::vec3(xNormalized, yNormalized, 0);
}

void StrGuiComponent::setPosition(const glm::vec2 &newPosition)
{
    StrGuiComponent::position = glm::vec3(newPosition.x, newPosition.y, 0);
}

const glm::vec3 &StrGuiComponent::getPosition() const
{
    return position;
}

void StrGuiComponent::setText(const std::string &text)
{
    StrGuiComponent::text = text;
}
