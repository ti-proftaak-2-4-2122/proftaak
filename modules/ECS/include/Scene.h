//
// Created by Daan van Donk on 10/05/2022.
//
#pragma once

#include <vector>
#include "GameObject.h"

class Scene
{
public:
    std::vector<GameObject *> gameobjects;

    void AddGameObject(GameObject *gameObject);
    void RemoveGameObject(GameObject*& gameObject);

    void update();

    Scene();
};

