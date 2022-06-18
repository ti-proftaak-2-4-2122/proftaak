/**
 * @file
 * @brief Source file for the Scene class
 * @author Daan van Donk
 * @date 10-05-2022
 */

#include <stdexcept>

#include "Scene.h"
#include "Collider.h"
#include "GLFW/glfw3.h"
#include "CharacterStats.h"

void Scene::AddGameObject(GameObject *gameObject)
{
    auto pos = std::find(
            this->gameobjects.begin(),
            this->gameobjects.end(),
            gameObject
    );

    if(pos != this->gameobjects.end())
        throw std::invalid_argument("GameObject was already added to scene");
    gameObject->Awake();
    gameobjects.push_back(gameObject);
}

/**
 * Removes the GameObject from the scene and destroys the GameObject
 * @param gameObject The pointer to GameObject to destroy.
 * If the deletion was successful, gameObject will be nullptr.
 * Don't use the GameObject after calling this function!
 */
void Scene::RemoveGameObject(GameObject* gameObject)
{
    auto pos = std::find(
        this->gameobjects.begin(),
        this->gameobjects.end(),
        gameObject
    );

    // If gameObject is in vector, remove
    if(pos != this->gameobjects.end()) {

        auto* collider = gameObject->FindComponent<Collider>();
        if(collider)
        {
            Collider::CleanUp(collider);
        }
        this->gameobjects.erase(pos);

        delete gameObject;
       gameObject = nullptr;
    }
}

/**
 * The Scene update checks if one of the players has won
 * This is wholly dependend on if they defeated 2 towers
 * of their on the opponents side.
 */
void Scene::update()
{
    this->currencyManager.update();
}

Scene::~Scene()
{
    for (auto gameObject: this->gameobjects)
        delete gameObject;
}

std::vector<GameObject *> Scene::findGameObjects(TagEnum tagEnum)
{
    auto foundObjects = std::vector<GameObject *>();

    for (auto* gameObject: this->gameobjects)
    {
        if (gameObject->getTagEnum() == tagEnum)
            foundObjects.push_back(gameObject);
    }

    return foundObjects;
}

bool Scene::checkPlayerWinCondition()
{
    if(this->team_1_towerDestroyed == 1)
    {
        std::cout << "Team 2 WINS" << std::endl;
        return true;
    }
    if (this->team_2_towerDestroyed == 1)
    {
        std::cout << "Team 1 WINS" << std::endl;
        return true;
    }
    return false;
}


CurrencyManager& Scene::getCurrencyManager()
{
    return this->currencyManager;
}