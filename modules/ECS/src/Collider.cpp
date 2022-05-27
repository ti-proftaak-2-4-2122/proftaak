//
// Created by Daan van Donk on 24/05/2022.
//

#include "Collider.h"
#include "Transform.h"

Collider::Collider(float radius) : radius(radius) {

}

void Collider::CheckCollision(Collider* other)
{
    glm::vec3 pos= gameObject->transform.getPosition();
    glm::vec3 otherPos = other->gameObject->transform.getPosition();
    //Distance calculation between this collider and other collider
    double distance = sqrt((((otherPos.x+other->radius)-(pos.x+this->radius))*(
            (otherPos.x+other->radius)-
            (pos.x+this->radius))) + (((otherPos.y+other->radius)-(pos.y+this->radius))*(
                    (otherPos.y+other->radius)-(pos.y+this->radius))));

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

