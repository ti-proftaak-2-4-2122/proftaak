/**
 * @file
 * @brief Header file for the Component class
 * @author Daan van Donk
 * @date 10-05-2022
 */

#pragma once

#include "GameObject.h"

class GameObject;

/**
 * @brief Abstract component, which gets inherited from derived components
 * Always has a reference to the gameObject that owns it.
 */
class Component
{
protected:
    GameObject *gameObject = nullptr;
public:

    GameObject* getGameObject();

    /**
     * @brief Awake is for "initializing" components,
     *
     */
    virtual void Awake() {};

    /**
     * @brief Update that gets overridden based on the component with a certain behaviour
     * Is used to update necessary variables within the behaviour.
     */
    virtual void Update() {};

    /**
     * @brief Draws the @Mesh of a GameObject.
     */
    virtual void Draw() {};

    /**
     * @brief is for updating variables that need to change after drawing the GameObject that it's attached to.
     */
    virtual void UpdateAfterDraw() {};

    Component();

    /**
     * @brief Sets the Parent which the component needs to be attached to.
     * @param parentGameObject is the parent that this component needs to attach/refer to.
     */
    void SetParent(GameObject *parentGameObject);

    virtual ~Component() = default;
};


