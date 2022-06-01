//
// Created by Daan van Donk on 10/05/2022.
//

#ifndef PROFTAAK24_COMPONENT_H
#define PROFTAAK24_COMPONENT_H

#include "GameObject.h"

class GameObject;

class Component
{
protected:
    GameObject *gameObject = nullptr;
public:
    virtual void Awake() {};

    virtual void Update() {};

    virtual void Draw() {};

    Component();

    void SetParent(GameObject *parentGameObject);

    virtual ~Component() = default;
};


#endif //PROFTAAK24_COMPONENT_H
