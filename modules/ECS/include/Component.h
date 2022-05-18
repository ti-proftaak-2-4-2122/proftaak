//
// Created by Daan van Donk on 10/05/2022.
//

#pragma once

#include "GameObject.h"
class GameObject;

class Component
{
protected:
    GameObject* gameObject;
public:
    virtual void Awake(){};
    virtual void Update(){};
    virtual void Draw(){};
    Component();
    void SetParent(GameObject* parentGameObject);
};


