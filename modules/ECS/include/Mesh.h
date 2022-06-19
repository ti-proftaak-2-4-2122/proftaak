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

/**
 * @class Mesh of GameObject a mesh can be defined as an object that renders enacts the GameObjects behaviour
 */
class Mesh : public Component
{
public:

    /**
     * @brief
     * @param _objmodel
     */
    explicit Mesh(ObjModel *_objmodel);

    /**
     * @brief Sets colour of mesh based on ObjectLoader
     * @param color
     */
    void SetColor(const glm::vec4& color);
    void SetMesh(ObjModel* model);
    /**
     * Sets the alpha channel for the mesh during drawing
     * @param alpha Alpha value. 0.0f is completely transparent, 1.0f is completely visible
     */
    void SetAlpha(float alpha);

    /**
     * @brief Sets the @parentTransform.
     */
    void Awake() override;

    /**
     * @brief Draws the mesh based on the incoming @objModel,
     * Does the drawing with VBO to save performance.
     */
    void Draw() override;

private:
    ObjModel *objModel;
    glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
    ParentTransform* parentTransform = nullptr;
};