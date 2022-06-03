//
// Created by Daan van Donk on 11/05/2022.
//

#pragma once

#include "vector"
#include "TagEnum.h"
#include <typeinfo>
#include <iostream>
#include <functional>

class Component;
class Transform;
class Collider;

class GameObject
{
private:
    std::vector<std::reference_wrapper<Component>> components;

public:
    Transform& transform;
    GameObject(Transform& transform1);

    TagEnum tagEnum;

    Component &AddComponent(Component *component);

    template<class T>
    T& FindComponent()
    {
        for (auto component : this->components)
        {
            auto derived = dynamic_cast<T*>(component.get());

            if (derived)
                return component;
        }

        return nullptr;
    }

    const std::vector<std::reference_wrapper<Component>>& getComponents() const;

    template<class T>
    T& AddComponent()
    {
        auto component = new T();
        this->AddComponent(component);
        return *component;
    }

    void AddChild(GameObject* child);
    void RemoveChild(GameObject*& child);

    virtual void Awake();

    virtual void Update();

    void Draw();

    ~GameObject();

    virtual void onTriggerEnter(Collider* other) {
        std::cout << "On Trigger Enter called" << std::endl;
    };

    virtual void onTriggerExit(Collider* other) {
        std::cout << "On Trigger Exit called" << std::endl;
    };

};

