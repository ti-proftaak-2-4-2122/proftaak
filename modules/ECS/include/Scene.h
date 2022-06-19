/**
 * @file
 * @brief Header file for the Scene class
 * @author Daan van Donk
 * @date 10-05-2022
 */
#pragma once

#include <vector>
#include "GameObject.h"
#include "CurrencyManager.h"

/**
 * @class Manager of the application to activate GameObject to enact their own behaviours.
 * @brief Keeps a list of GameObjects to update.
 * When a Game Object is no longer needed the scene will remove this from @gameObjects with the func @RemoveGameObject
 */
class Scene
{
public:
    /**
     * @brief Singleton getter, is protected against multi-threading
     * @TODO Update to be it a mutex
     * @return
     */
    static Scene& getSingleton()
    {
        if(!singleton)
        {
            singleton = new Scene();
        }

        return *singleton;
    }

    std::vector<GameObject *> gameobjects;
    short team_1_towerDestroyed = -1;
    short team_2_towerDestroyed = -1;

    /**
     * @brief Adds a GameObject to the @gameobjects
     * @param gameObject to be added to @gameobjects / added to the @Scene
     */
    void AddGameObject(GameObject *gameObject);

    /**
     * @brief Removes GameObject from the list @gameobjects
     * @param gameObject the GameObject that needs to be removed from the @Scene
     */
    void RemoveGameObject(GameObject* gameObject);

    /**
     * @brief Checks if Team 1 or Team 2 has won
     * @return whether Team 1 has won or Team 2, based on @team_1_towerDestroyed or @team_2_towerDestroyed
     */
    bool checkPlayerWinCondition();


    /**
     * @brief Function to find a specific GameObject based on a @TagEnum, be it a GUI GameObject or whatever else.
     * @param tagEnum The tag of the GameObject that we want to find withing @gameobjects
     * @return
     */
    std::vector<GameObject *> findGameObjects(TagEnum tagEnum);

    /**
     * @brief Updates the Scene
     */
    void update();

    /**
     * @brief Simple Getter for the @CurrencyManager
     * @return the currency manager to be able to spawn a unit in.
     */
    CurrencyManager& getCurrencyManager();

private:
    inline static Scene* singleton = nullptr;

    CurrencyManager currencyManager;

    Scene() : currencyManager(CurrencyManager(2, 1.0f, 0.8f, 10.0f))
    {
        gameobjects = std::vector<GameObject *>();
    }
    ~Scene();

};

