/**
 * @file
 * @brief Source file for the Component class
 * @author Ewout
 * @date 17-05-2022
 */

#include "Component.h"

void Component::SetParent(GameObject *parentGameObject)
{
    gameObject = parentGameObject;
}

GameObject *Component::getGameObject()
{
    return gameObject;
}

Component::Component()
= default;
