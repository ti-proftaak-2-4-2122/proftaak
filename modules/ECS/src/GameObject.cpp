//
// Created by Daan van Donk on 10/05/2022.
//

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"

void GameObject::AddComponent(Component *component) {
    component->SetParent(this);
    components.push_back(component);
}

GameObject::GameObject() : transform((this->AddComponent<Transform>()))
{

}
template<class T> T& GameObject::AddComponent()
{
    auto component = new T();
    AddComponent(component);
    return *component;
}

Transform &GameObject::getTransform()
{
    return *((Transform*) components[0]);
}
