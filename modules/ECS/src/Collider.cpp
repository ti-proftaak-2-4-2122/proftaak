//
// Created by Daan van Donk on 24/05/2022.
//

#include "Collider.h"
Collider::Collider(float radius, glm::vec3 position) : radius(radius), position(position) {

}

void Collider::CheckCollision(Collider* other)
{
    //Distance calculation between this collider and other collider
    double distance = sqrt((((other->position.x+other->radius)-(this->position.x+this->radius))*(
            (other->position.x+other->radius)-
    (this->position.x+this->radius))) + (((other->position.y+other->radius)-(this->position
            .y+this->radius))*(
            (other->position.y+other->radius)-(this->position.y+this->radius))));

    if(distance <= this->radius + other->radius) {
        if(!hasEntered) {
            gameObject->onTriggerEnter(other);
            hasEntered = true;
        }
    } else {
        if(hasEntered) {
            gameObject->onTriggerExit(other);
            hasEntered = false;
        }
    }
}

void Collider::Update()
{
    Component::Update();
    for(auto other : otherColliders) {
        CheckCollision(other);
    }
}

