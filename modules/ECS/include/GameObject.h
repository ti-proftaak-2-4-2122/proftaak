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
public:
    std::vector<Component *> components;
    Transform &transform;
    GameObject();

    TagEnum tagEnum;

    Component &AddComponent(Component *component);

    template<class T>
    T *FindComponent()
    {
        for (auto component: components)
        {
            auto derived = dynamic_cast<T *>(component);
            if (derived)
            {
                //outComponent = derived;
                return derived;
            }
        }
        return nullptr;
    }

    template<class T>
    T &AddComponent();

    virtual void onTriggerEnter(Collider* collider) {
        std::cout << "On Trigger Enter called" << std::endl;
    };
};

