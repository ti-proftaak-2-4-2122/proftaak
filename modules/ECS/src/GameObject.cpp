//
// Created by Daan van Donk on 10/05/2022.
//

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "ParentTransform.h"
#include <typeinfo>
#include <stdexcept>

GameObject::GameObject() : transform((this->AddComponent<Transform>()))
{

}

Component &GameObject::AddComponent(Component *component)
{
    component->SetParent(this);
    components.push_back(component);
    return *component;
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

/**
 * Removes the Child from the GameObject and destroys the child
 * @param gameObject The pointer to GameObject-child to destroy.
 * If the deletion was successful, child will be nullptr.
 * Don't use the GameObject-child after calling this function!
 */
void GameObject::RemoveChild(GameObject *&child)
{
    auto pos = std::find(
            this->children.begin(),
            this->children.end(),
            child
    );

    // If gameObject is in vector, remove
    if(pos != this->children.end()) {
        this->children.erase(pos);

        delete child;
        child = nullptr;
    }
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

GameObject::~GameObject()
{
    for(auto child : this->children)
        delete child;

    for(auto component : this->components)
        delete component;
}
