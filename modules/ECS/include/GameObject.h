//
// Created by Daan van Donk on 11/05/2022.
//

#pragma once

#include "vector"

class Component;

class GameObject
{

public:
    std::vector<Component *> components;

    void AddComponent(Component *component);

    GameObject();

    template<class T>
    T& AddComponent();
};

