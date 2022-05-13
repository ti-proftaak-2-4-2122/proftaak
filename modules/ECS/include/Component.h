//
// Created by Daan van Donk on 10/05/2022.
//

#ifndef PROFTAAK24_COMPONENT_H
#define PROFTAAK24_COMPONENT_H

#include "GameObject.h"

class Component
{
public:
    GameObject::GameObject* parentGO;

    virtual void Awake(){};
    virtual void Update(){};
    virtual void Draw(){};
};


#endif //PROFTAAK24_COMPONENT_H
