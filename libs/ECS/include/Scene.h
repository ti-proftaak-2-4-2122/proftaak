//
// Created by Daan van Donk on 10/05/2022.
//

#ifndef PROFTAAK24_SCENE_H
#define PROFTAAK24_SCENE_H


#include <vector>
#include "GameObject.h"

class Scene
{
public:
    std::vector<GameObject> gameobjects;
    float deltaTime;
};


#endif //PROFTAAK24_SCENE_H
