//
// Created by Daan van Donk on 10/05/2022.
//

#pragma once

#include "Scene.h"

class SceneManager
{
public:
    static void LoadScene(Scene &scene);

    static void UpdatePoll(Scene &scene);
};