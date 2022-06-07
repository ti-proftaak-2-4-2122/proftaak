//
// Created by Ewout on 1-6-2022.
//

#include "gui/Gui.h"
#include "tigl.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Transform.h"
#include <TextureLoader.h>

#define ATLAS_WIDTH 32
#define ATLAS_HEIGHT 32

void Gui::Draw()
{
    tigl::shader->setProjectionMatrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 200.0f));
    tigl::shader->setViewMatrix(glm::lookAt(
            glm::vec3(0.0f, 0, 5),
            glm::vec3(0.0f, 0, 0),
            glm::vec3(0.0f, 1, 0)
    ));

    auto position = this->gameObject->transform.getPosition();
    auto modelMatrix = glm::mat4(1.0f);
    tigl::shader->setModelMatrix(glm::translate(modelMatrix, position));

    glBindTexture(GL_TEXTURE_2D, fontTxId);
    tigl::shader->enableTexture(true);
    auto textureIndex = 2;

    const float textureWidth = 1.0f / ATLAS_WIDTH;
    const float textureHeigth = 1.0f / ATLAS_HEIGHT;

    const float tx0 = (textureIndex % ATLAS_WIDTH) * textureWidth;
    const float tx1 = tx0 + textureWidth;
    const float ty0 = (textureIndex / ATLAS_HEIGHT) * textureHeigth;
    const float ty1 = ty0 + textureHeigth;
    tigl::begin(GL_QUADS);

    tigl::addVertex(tigl::Vertex::PT(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(tx1, ty1)));
    tigl::addVertex(tigl::Vertex::PT(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(tx0, ty1)));
    tigl::addVertex(tigl::Vertex::PT(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(tx0, ty0)));
    tigl::addVertex(tigl::Vertex::PT(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(tx1, ty0)));
    tigl::end();

    tigl::shader->enableTexture(false);

}

Gui::Gui()
{
    fontTxId = textureLoader::getTexture("../resource/textures/Courier.png");


}