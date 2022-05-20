//
// Created by Daan van Donk on 11/05/2022.
//

#pragma once

#include "vector"
#include <typeinfo>

class Component;

class Transform;

class GameObject
{
public:
    std::vector<Component *> components;
    Transform &transform;

    GameObject();

    Component &AddComponent(Component *component);

    template<class T>
    bool TryFindComponent(T *outComponent)
    {
        for (auto component: components)
        {
            auto derived = dynamic_cast<T *>(component);
            if (derived)
            {
                outComponent = derived;
                return true;
            }
        }
        outComponent = nullptr;
        return false;
    }

    template<class T>
    T &AddComponent();
};

