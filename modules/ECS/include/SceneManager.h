//
// Created by Daan van Donk on 10/05/2022.
//

#pragma once

#include "Scene.h"
#include "Collider.h"

class SceneManager
{
public:
    static void LoadScene(Scene &scene);

    static void UpdatePoll(Scene &scene);

    static std::vector<Collider*> GetAllComponents(Scene& scene);
};