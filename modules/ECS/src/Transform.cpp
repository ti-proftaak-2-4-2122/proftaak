//
// Created by Ewout on 13-5-2022.
//

#include "Transform.h"

Transform::Transform()
{
    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);
}

Transform::Transform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
        : position(position), rotation(rotation), scale(scale) {}

const glm::vec3 &Transform::getPosition() const
{
    return position;
}

void Transform::setPosition(const glm::vec3 &newPosition)
{
    position = newPosition;

}

const glm::vec3 &Transform::getRotation() const
{
    return rotation;
}

void Transform::setRotation(const glm::vec3 &newRotation)
{
    rotation = glm::radians(newRotation);
}

const glm::vec3 &Transform::getScale() const
{
    return scale;
}

void Transform::setScale(const glm::vec3 &newScale)
{
    Transform::scale = newScale;
}




