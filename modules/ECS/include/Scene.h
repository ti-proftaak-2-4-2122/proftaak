/**
 * @file
 * @brief Header file for the Scene class
 * @author Daan van Donk
 * @date 10-05-2022
 */
#pragma once

#include <vector>
#include "GameObject.h"

class Scene
{

private:
    inline static Scene* singleton = nullptr;

    Scene() {
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


    std::vector<GameObject *> findGameObjects(TagEnum tagEnum);

    void update();
};

