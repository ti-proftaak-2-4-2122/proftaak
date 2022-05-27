//
// Created by Daan van Donk on 10/05/2022.
//

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "ParentTransform.h"
#include <typeinfo>
#include <stdexcept>



Component &GameObject::AddComponent(Component *component)
{
    component->SetParent(this);
    components.push_back(component);
    return *component;
}

GameObject::GameObject(Transform* _transform) : transform(*_transform)
{
    this->AddComponent(&transform);
}

void GameObject::AddChild(GameObject* child)
{
    if(child->FindComponent<ParentTransform>() != nullptr)
        throw std::invalid_argument("child cannot already have a parent transform");

    if(child == this)
        throw std::invalid_argument("Parent cannot contain itself as child");

    this->children.push_back(child);
    child->AddComponent(new ParentTransform(this));
}

void GameObject::Awake()
{
    for(auto component : this->components)
        component->Awake();

    for(auto child : this->children)
        child->Awake();
}

void GameObject::Update()
{
    for(auto component : this->components)
        component->Update();

    for(auto child : this->children)
        child->Update();
}

void GameObject::Draw()
{
    for(auto component : this->components)
        component->Draw();

    for(auto child : this->children)
        child->Draw();
}