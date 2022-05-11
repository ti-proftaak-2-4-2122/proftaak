//
// Created by Daan van Donk on 10/05/2022.
//

#include <future>
#include "SceneManager.h"

void UpdatePoll(Scene scene);

void SceneManager::LoadScene(Scene scene)
{
    for (GameObject gameObject: scene.gameobjects)
    {
        for (Component *component: gameObject.components)
        {
            component->Awake();
        }
    }

     auto f = std::async(std::launch::async, UpdatePoll, scene);
}

void UpdatePoll(Scene scene) {
    while(1) {
        for (GameObject gameObject: scene.gameobjects)
        {
            for (Component *component: gameObject.components)
            {
                component->Update();
            }
        }
    }
}