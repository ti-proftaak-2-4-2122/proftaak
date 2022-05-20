//
// Created by Daan van Donk on 10/05/2022.
//
#pragma once

#include <vector>
#include "GameObject.h"

class Scene
{
protected:

    static float deltaTime;
public:
    std::vector<GameObject *> gameobjects;

    void AddGameObject(GameObject *gameObject);

    void update();

    static float GetDeltaTime()
    {
        return deltaTime;
    };

    Scene();
};

