/**
 * @file
 * @brief Header file for the SceneManager class
 * @author Daan van Donk
 * @date 10-05-2022
 */

#pragma once

#include "Scene.h"
#include "Collider.h"

/**
 * @brief Manager To load the scene and update the necessary GameObjects withing the scene
 */
class SceneManager
{
public:
    static void LoadScene(Scene &scene);

    static void UpdatePoll(Scene &scene);

    static std::vector<Collider*> GetAllComponents(Scene& scene);
};