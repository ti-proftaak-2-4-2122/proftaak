//
// Created by Daan van Donk on 10/05/2022.
//

#include <future>
#include "SceneManager.h"
#include "Component.h"

void UpdatePoll(Scene scene);

void SceneManager::LoadScene(Scene &scene)
{
    for (auto gameObject : scene.gameobjects)
        gameObject->Awake();
}

void SceneManager::UpdatePoll(Scene &scene)
{
    for (const auto &gameObject : scene.gameobjects)
        gameObject->Update();

    for (const auto &gameObject : scene.gameobjects)
        gameObject->Draw();
}