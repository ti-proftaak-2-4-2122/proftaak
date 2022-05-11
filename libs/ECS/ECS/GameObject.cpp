//
// Created by Daan van Donk on 10/05/2022.
//

#include "../include/GameObject.h"

void GameObject::AddComponent(Component *component) {
    components.push_back(component);
}
