//
// Created by Daan van Donk on 10/05/2022.
//

#include <future>
#include "SceneManager.h"
#include "Component.h"

void UpdatePoll(Scene scene);

void SceneManager::LoadScene(Scene &scene)
{
    for (auto gameObject: scene.getGameobjects())
    {
        for (auto *component: gameObject->components)
        {
            component->Awake();
        }
    }
    //auto f = std::async(std::launch::async, UpdatePoll, scene);
    //UpdatePoll(scene);
}

void SceneManager::UpdatePoll(Scene &scene)
{
    for (const auto &gameObject: scene.getGameobjects())
    {
        for (auto *component: gameObject->components)
        {
            component->Update();
            component->Draw();
        }
    }
}