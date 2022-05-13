//
// Created by Daan van Donk on 10/05/2022.
//

#include "ECS/include/Scene.h"

void Scene::AddGameObject(GameObject gameObject) {
    gameobjects.push_back(gameObject);
}