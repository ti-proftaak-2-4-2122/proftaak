/**
 * @file
 * @brief Source file for the Collider class
 * @author Daan van Donk
 * @date 24-05-2022
 */

#include "Collider.h"
#include "Transform.h"

Collider::Collider(float radius) : radius(radius) {}

void Collider::CheckCollision(Collider *other)
{
    glm::vec3 pos = gameObject->transform.getPosition();
    glm::vec3 otherPos = other->gameObject->transform.getPosition();

    auto distance = glm::distance(otherPos, pos);

    if (distance <= (this->radius + other->radius))
    {
        //Collision occurred
        if (!hasEntered)
        {
            gameObject->onTriggerEnter(other);
            hasEntered = true;
        }
    } else
    {
        if (hasEntered)
        {
            gameObject->onTriggerExit(other);
            hasEntered = false;
        }
    }
}

void Collider::Update()
{
    Component::Update();
    for (auto other: otherColliders)
    {
        if (other == this)
            continue;
        CheckCollision(other);
    }
}

void Collider::CleanUp(Collider *collider)
{
    auto pos = std::find(
            otherColliders.begin(),
            otherColliders.end(),
            collider
    );

    std::cout << " Erasing collider from list" << std::endl;

    otherColliders.erase(pos);
}

void Collider::addCollider(Collider *collider)
{
    auto pos = std::find(
            otherColliders.begin(),
            otherColliders.end(),
            collider
    );

    if (pos == otherColliders.end())
    {
        otherColliders.push_back(collider);
    }
}

