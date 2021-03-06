//
// Created by Ewout on 10-6-2022.
//

#pragma once

#include "Component.h"
#include <string>
#include "glm/glm.hpp"
#include <glad/glad.h>

/**
 * @class Gui Component which display necessary data,
 * such as a cost and health onto the screen.
 */
class StrGuiComponent : public Component
{
public:
    void UpdateAfterDraw() override;

    void setPosition(const glm::vec3 &position);

//    explicit StrGuiComponent(const std::string &textString,
//        const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
//        const glm::vec3 &scale = glm::vec3(0.0f, 0.0f, 0.0f));
    explicit StrGuiComponent(std::string text, const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
                             const glm::vec3 &scale = glm::vec3(1.0f, 1.0f, 1.0f));

    [[maybe_unused]] void setPosition(const glm::vec2 &newPosition);

    [[maybe_unused]] void setScale(const glm::vec3& newScale);

    [[nodiscard]] const glm::vec3 &getPosition() const;

    void setText(const std::string &text);

    void setColor(const glm::vec4 color);

private:
    glm::vec3 position{};
    glm::vec3 scale{};
    GLuint fontTxId;

    glm::vec4 color { 0.0f, 0.0f, 0.0f, 1.0f };

    static void DrawChar(glm::mat4 &modelMatrix, char characteristic);

    std::string text;
};



