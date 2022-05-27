//
// Created by Daan van Donk on 10/05/2022.
//

#include "Scene.h"

void Scene::AddGameObject(GameObject *gameObject)
{

    gameobjects.push_back(gameObject);
    AddColliderObject(*gameObject);
}



Scene::Scene()
{
    gameobjects = std::vector<GameObject *>();
    colliders = std::vector<Collider *>();
}

void Scene::update()
{

    for (auto *collider: colliders)
    {
        collider->CheckColliders(colliders);
    }
}

void Scene::AddColliderObject(GameObject &gameObject)
{
    auto* collider = gameObject.FindComponent<Collider>();
    if (collider){
        colliders.push_back(collider);
    }

}

const std::vector<GameObject *> &Scene::getGameobjects() const
{
    return gameobjects;
}

const std::vector<Collider *> &Scene::getColliders() const
{
    return colliders;
}
