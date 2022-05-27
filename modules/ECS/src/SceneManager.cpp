//
// Created by Daan van Donk on 10/05/2022.
//

#include <future>
#include "SceneManager.h"
#include "Component.h"

void UpdatePoll(Scene scene);

void SceneManager::LoadScene(Scene &scene)
{
    for (auto gameObject: scene.gameobjects)
    {
        for (auto *component: gameObject->components)
        {
            component->Awake();
        }
    }

    GetAllComponents<Collider>();

    //auto f = std::async(std::launch::async, UpdatePoll, scene);
    //UpdatePoll(scene);
}

void SceneManager::UpdatePoll(Scene &scene)
{
    for (const auto &gameObject : scene.gameobjects)
        gameObject->Update();

    for (const auto &gameObject : scene.gameobjects)
        gameObject->Draw();
}

