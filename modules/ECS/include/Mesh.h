/**
 * @file
 * @brief Header file for the Mesh class
 * @author Daan van Donk
 * @date 12-05-2022
 */

#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "Component.h"
#include "tigl.h"
#include "ObjModel.h"
#include "Transform.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

class ObjModel;

class GameObject;

class ParentTransform;

class Mesh : public Component
{
private:
    ObjModel *objModel;
    glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
    ParentTransform* parentTransform = nullptr;
public:

    explicit Mesh(ObjModel *_objmodel);

    void SetColor(const glm::vec4& color);
    /**
     * Sets the alpha channel for the mesh during drawing
     * @param alpha Alpha value. 0.0f is completely transparent, 1.0f is completely visible
     */
    void SetAlpha(float alpha);

    void Awake() override;
    void Draw() override;
};