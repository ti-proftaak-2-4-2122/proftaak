//
// Created by Daan van Donk on 10/05/2022.
//
#pragma once

#include <vector>
#include "GameObject.h"
#include "CurrencyManager.h"

class Scene
{

private:
    inline static Scene* singleton = nullptr;

    CurrencyManager currencyManager;

    Scene() : currencyManager(CurrencyManager(2, 1.0f, 0.8f, 10.0f))
    {
        gameobjects = std::vector<GameObject *>();
    }
    ~Scene();

public:
    static Scene& getSingleton()
    {
        if(!singleton)
        {
            singleton = new Scene();
        }

        return *singleton;
    }


    std::vector<GameObject *> gameobjects;

    void AddGameObject(GameObject *gameObject);
    void RemoveGameObject(GameObject* gameObject);

    void update();

    CurrencyManager& getCurrencyManager();
};

