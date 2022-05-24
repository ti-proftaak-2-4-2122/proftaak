//
// Created by Daan van Donk on 10/05/2022.
//

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include <typeinfo>

GameObject::GameObject() : transform((this->AddComponent<Transform>()))
{

}

Component &GameObject::AddComponent(Component *component)
{
    component->SetParent(this);
    components.push_back(component);
    return *component;
}

void GameObject::Awake()
{
    for(auto component : this->components)
        component->Awake();
}

void GameObject::Update()
{
    for(auto component : this->components)
        component->Update();
}

void GameObject::Draw()
{
    for(auto component : this->components)
        component->Draw();
}