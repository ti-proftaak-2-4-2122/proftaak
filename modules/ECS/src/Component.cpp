//
// Created by Ewout on 17-5-2022.
//
#include "Component.h"

void Component::SetParent(GameObject *parentGameObject)
{
    gameObject = parentGameObject;
}

Component::Component()
{

}
