/**
 * @file
 * @brief Source file for the ParentTransform class
 * @author twanh
 * @date 20-05-2022
 */

#include <glm/gtc/matrix_transform.hpp>

#include "ParentTransform.h"
#include "Transform.h"

ParentTransform::ParentTransform(GameObject *parent)
    : parent(parent)
{

}

inline Transform &ParentTransform::GetParentTransform()
{
    return this->parent->transform;
}

glm::mat4 ParentTransform::GetParentModelMatrix()
{
    glm::mat4 result(1.0f);

    auto transform = this->GetParentTransform();

    result = glm::scale(result, transform.getScale());

    result = glm::translate(result, transform.getPosition());

    auto rotation = transform.getRotation();
    result = glm::rotate(result, rotation.x, glm::vec3(1, 0, 0));
    result = glm::rotate(result, rotation.y, glm::vec3(0, 1, 0));
    result = glm::rotate(result, rotation.z, glm::vec3(0, 0, 1));

    return result;
}