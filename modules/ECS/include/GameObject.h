//
// Created by Daan van Donk on 11/05/2022.
//

#include "Transform.h"
#include "vector"
#include "Component.h"

#ifndef PROFTAAK24_GAMEOBJECT_H
#define PROFTAAK24_GAMEOBJECT_H

class GameObject {
public:
    std::vector<Component*> components;
    void AddComponent(Component* component);
    GameObject() {
        this->AddComponent(new Transform);
    }
};
#endif //PROFTAAK24_GAMEOBJECT_H
