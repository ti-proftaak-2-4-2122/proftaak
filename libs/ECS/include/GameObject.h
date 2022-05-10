//
// Created by Daan van Donk on 10/05/2022.
//

#ifndef PROFTAAK24_GAMEOBJECT_H
#define PROFTAAK24_GAMEOBJECT_H


#include "Component.h"
#include "Vector3.h"
#include "Transform.h"


class GameObject
{
public:
    std::vector<Component> components;
    Transform transform;
};


#endif //PROFTAAK24_GAMEOBJECT_H
