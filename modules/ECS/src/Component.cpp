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

Component::Component()
= default;
