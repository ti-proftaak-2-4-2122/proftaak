//
// Created by Daan van Donk on 10/05/2022.
//

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"

Component &GameObject::AddComponent(Component *component)
{
    component->SetParent(this);
    components.push_back(component);
    return *component;
}

GameObject::GameObject() : transform((this->AddComponent<Transform>()))
{

}