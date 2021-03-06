/**
 * @file
 * @brief Source file for the GameObject class
 * @author Daan van Donk
 * @date 10-05-2022
 */

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include "ParentTransform.h"
#include <stdexcept>

Component &GameObject::AddComponent(Component *component)
{
    auto pos = std::find(
            this->components.begin(),
            this->components.end(),
            component
    );

    if (pos != this->components.end())
        throw std::invalid_argument("Component was already added to GameObject");

    component->SetParent(this);
    components.push_back(component);
    return *component;
}

GameObject::GameObject(Transform *_transform) : transform(*_transform)
{
    this->AddComponent(&transform);
}

GameObject::GameObject() : transform((this->AddComponent<Transform>()))
{

}

void GameObject::AddChild(GameObject *child)
{
    if (child->FindComponent<ParentTransform>() != nullptr)
        throw std::invalid_argument("child cannot already have a parent transform");

    if (child == this)
        throw std::invalid_argument("Parent cannot contain itself as child");

    auto pos = std::find(
            this->children.begin(),
            this->children.end(),
            child
    );

    if (pos != this->children.end())
        throw std::invalid_argument("GameObject already contains child");

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
    if (pos != this->children.end())
    {
        this->children.erase(pos);

        delete child;
        child = nullptr;
    }
}

void GameObject::Awake()
{
    for (auto component: this->components)
        component->Awake();

    for (auto child: this->children)
        child->Awake();
}

void GameObject::Update()
{
    for (auto component: this->components)
        component->Update();

    for (auto child: this->children)
        child->Update();
}

void GameObject::Draw()
{
    for (auto component: this->components)
        component->Draw();

    for (auto child: this->children)
        child->Draw();
}

void GameObject::UpdateAfterDraw()
{
    for (auto component: this->components)
        component->UpdateAfterDraw();

    for (auto child: this->children)
        child->UpdateAfterDraw();
}

GameObject::~GameObject()
{
    for (auto child: this->children)
        delete child;

    for (auto component: this->components)
        delete component;
}

const std::vector<Component *> &GameObject::getComponents() const
{
    return components;
}

TagEnum GameObject::getTagEnum() const
{
    return tagEnum;
}

void GameObject::setTagEnum(TagEnum newTagEnum)
{
    GameObject::tagEnum = newTagEnum;
}
