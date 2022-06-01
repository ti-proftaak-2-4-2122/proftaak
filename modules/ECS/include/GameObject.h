//
// Created by Daan van Donk on 11/05/2022.
//

#pragma once

#include "vector"
#include "TagEnum.h"
#include <typeinfo>
#include <iostream>

class Component;
class Transform;
class Collider;

class GameObject
{
private:
    std::vector<Component *> components;
    std::vector<GameObject*> children;

public:
    Transform &transform;
    GameObject();

    TagEnum tagEnum;

    Component &AddComponent(Component *component);

    template<class T>
    T *FindComponent()
    {
        for (auto component : this->components)
        {
            auto derived = dynamic_cast<T *>(component);

            if (derived)
                return derived;

        }

        return nullptr;
    }

    template<class T>
    T& AddComponent()
    {
        auto component = new T();
        this->AddComponent(component);
        return *component;
    }

    void AddChild(GameObject* child);
    void RemoveChild(GameObject*& child);

    void Awake();

    void Update();

    void Draw();


    ~GameObject();
    virtual void onTriggerEnter(Collider* collider) {
        std::cout << "On Trigger Enter called" << std::endl;
    };

    virtual void onTriggerExit(Collider* collider) {
        std::cout << "On Trigger Exit called" << std::endl;
    };

};

