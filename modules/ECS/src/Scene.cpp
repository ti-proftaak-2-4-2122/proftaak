//
// Created by Daan van Donk on 10/05/2022.
//

#include "Scene.h"

void Scene::AddGameObject(GameObject *gameObject)
{
    gameobjects.push_back(gameObject);
}

/**
 * Removes the GameObject from the scene and destroys the GameObject
 * @param gameObject The pointer to GameObject to destroy.
 * If the deletion was successful, gameObject will be nullptr.
 * Don't use the GameObject after calling this function!
 */
void Scene::RemoveGameObject(GameObject*& gameObject)
{
    auto pos = std::find(
        this->gameobjects.begin(),
        this->gameobjects.end(),
        gameObject
    );

    // If gameObject is in vector, remove
    if(pos != this->gameobjects.end()) {
        this->gameobjects.erase(pos);

        delete gameObject;
        gameObject = nullptr;
    }
}

Scene::Scene()
{
    gameobjects = std::vector<GameObject *>();
}

void Scene::update()
{

}
