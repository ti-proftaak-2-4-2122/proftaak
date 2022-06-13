//
// Created by Daan van Donk on 10/05/2022.
//

#include <future>
#include "SceneManager.h"
#include "Component.h"
#include <iostream>

void UpdatePoll(Scene scene);

std::vector<Collider *> SceneManager::GetAllComponents(Scene& scene)
{
    std::vector<Collider*> result;

    for(auto gameobject : scene.gameobjects) {
        Collider* component = gameobject->FindComponent<Collider>();

        if(component) {
            result.push_back(component);
        }
    }

    return result;
}

void SceneManager::LoadScene(Scene &scene)
{

    for (const auto &gameObject : scene.gameobjects)
    {
        //gameObject->Awake();
    }

    std::vector<Collider*> colliders = GetAllComponents(scene);
    for(Collider* collider : colliders) {
        for(Collider* collider1 : colliders) {
            if(collider == collider1) {
                continue;
            }
            Collider::addCollider(collider1);
        }
    }

    //auto f = std::async(std::launch::async, UpdatePoll, scene);
    //UpdatePoll(scene);
}

void SceneManager::UpdatePoll(Scene &scene)
{
    for (const auto &gameObject : scene.gameobjects)
        gameObject->Update();

    for (const auto &gameObject : scene.gameobjects)
        gameObject->Draw();

    for (const auto &gameObject : scene.gameobjects)
        gameObject->UpdateAfterDraw();
}
