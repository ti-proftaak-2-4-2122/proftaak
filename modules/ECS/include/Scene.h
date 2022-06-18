/**
 * @file
 * @brief Header file for the Scene class
 * @author Daan van Donk
 * @date 10-05-2022
 */
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
    short team_1_towerDestroyed = -1;
    short team_2_towerDestroyed = -1;

    void AddGameObject(GameObject *gameObject);
    void RemoveGameObject(GameObject* gameObject);
    bool checkPlayerWinCondition();


    std::vector<GameObject *> findGameObjects(TagEnum tagEnum);

    void update();

    CurrencyManager& getCurrencyManager();
};

