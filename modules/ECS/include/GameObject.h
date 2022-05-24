//
// Created by Daan van Donk on 11/05/2022.
//

#pragma once

#include "vector"

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
    T &AddComponent();

    virtual void onTriggerEnter() {};
};

