//
// Created by Ewout on 10-6-2022.
//

#pragma once

#include "Component.h"
#include <string>

class StrGuiComponent : public Component
{
private:
    glm::vec3 position{};
    glm::vec3 scale{};
    GLuint fontTxId;

    static void DrawChar(glm::mat4 &modelMatrix, char characteristic);

    std::string text;

public:
    void UpdateAfterDraw() override;

    void setPosition(const glm::vec3 &position);

//    explicit StrGuiComponent(const std::string &textString,
//        const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
//        const glm::vec3 &scale = glm::vec3(0.0f, 0.0f, 0.0f));
    explicit StrGuiComponent(std::string text, const glm::vec3 &position = glm::vec3(0.0f, 0.0f, 0.0f),
                    const glm::vec3 &scale = glm::vec3(1.0f, 1.0f, 1.0f));

    void setPosition(const glm::vec2 &newPosition);

    const glm::vec3 &getPosition() const;

    void setText(const std::string &text);
};



