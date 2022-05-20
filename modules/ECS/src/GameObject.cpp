//
// Created by Daan van Donk on 10/05/2022.
//

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"
#include <typeinfo>

Component &GameObject::AddComponent(Component *component)
{
    component->SetParent(this);
    components.push_back(component);
    return *component;
}

GameObject::GameObject() : transform((this->AddComponent<Transform>()))
{

}

template<class T>
T &GameObject::AddComponent()
{
    auto component = new T();
    AddComponent(component);
    return *component;
}

template<class T>
T &GameObject::FindComponent()
{
    for (auto component: components)
    {
        if (typeid(T) == typeid(*component))
        {
            return *((T*) component);
        }
    }

    return nullptr;
}
