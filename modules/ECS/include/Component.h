/**
 * @file
 * @brief Header file for the Component class
 * @author Daan van Donk
 * @date 10-05-2022
 */

#pragma once

#include "GameObject.h"

class GameObject;

class Component
{
protected:
    GameObject *gameObject = nullptr;
public:

    GameObject* getGameObject();
    virtual void Awake() {};

    virtual void Update() {};

    virtual void Draw() {};

    virtual void UpdateAfterDraw() {};

    Component();

    void SetParent(GameObject *parentGameObject);

    virtual ~Component() = default;
};


