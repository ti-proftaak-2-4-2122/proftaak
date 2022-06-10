/**
 * @file
 * @brief Source file for the Scene class
 * @author Daan van Donk
 * @date 10-05-2022
 */

#include <stdexcept>

#include "Scene.h"

void Scene::AddGameObject(GameObject *gameObject)
{
    auto pos = std::find(
            this->gameobjects.begin(),
            this->gameobjects.end(),
            gameObject
    );

    if(pos != this->gameobjects.end())
        throw std::invalid_argument("GameObject was already added to scene");

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

Scene::~Scene()
{
    for(auto gameObject : this->gameobjects)
        delete gameObject;
}
