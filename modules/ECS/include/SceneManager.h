//
// Created by Daan van Donk on 10/05/2022.
//

#pragma once

#include "Scene.h"

class SceneManager
{
public:
    static Scene* currentScene;
    static void LoadScene(Scene &scene);

    static void UpdatePoll(Scene &scene);

    template<class T>
    static std::vector<T*> GetAllComponents()
    {
        std::vector<T*> result;

        for(auto gameobject : currentScene->gameobjects) {
            T* component = gameobject->FindComponent<T>();

            if(component) {
                result.push_back(component);
            }
        }

        return result;
    }

};