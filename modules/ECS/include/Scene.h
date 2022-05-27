//
// Created by Daan van Donk on 10/05/2022.
//
#pragma once

#include <vector>
#include "GameObject.h"
#include "Collider.h"

class Scene
{

    std::vector<GameObject *> gameobjects;
    std::vector<Collider *> colliders;
public:

    const std::vector<GameObject *> &getGameobjects() const;

    const std::vector<Collider *> &getColliders() const;

    void AddGameObject(GameObject *gameObject);

    void AddColliderObject(GameObject &gameObject);

    void update();

    Scene();
};

