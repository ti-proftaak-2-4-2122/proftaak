//
// Created by Daan van Donk on 10/05/2022.
//

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include <typeinfo>
#include <stdexcept>

void GameObject::Awake()
{
    for(Component& component : this->components)
        component.Awake();
}

void GameObject::Update()
{
    for(Component& component : this->components)
        component.Update();
}

void GameObject::Draw()
{
    for(Component& component : this->components)
        component.Draw();
}

GameObject::~GameObject()
{
//    for(Component& component : this->components)
//        delete component;
}

const std::vector<std::reference_wrapper<Component>>&GameObject::getComponents() const
{
    return components;
}

GameObject::GameObject(Transform &transform1) : transform(transform1)
{

}
