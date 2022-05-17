//
// Created by Daan van Donk on 10/05/2022.
//

#include "GameObject.h"
#include "Transform.h"
#include "Component.h"

void GameObject::AddComponent(Component *component) {
    components.push_back(component);
}

GameObject::GameObject() {
    this->AddComponent(new Transform(this));
}