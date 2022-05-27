//
// Created by Daan van Donk on 24/05/2022.
//

#include "Collider.h"
Collider::Collider(float radius, glm::vec3 position) : radius(radius), position(position) {

}

bool Collider::CheckCollision(glm::vec3 position2, float radius2)
{
    double distance = sqrt((((position2.x+radius2)-(this->position.x+this->radius))*((position2.x+radius2)-
    (this->position.x+this->radius))) + (((position2.y+radius2)-(this->position.y+this->radius))*((position2.y+radius2)-(this->position.y+this->radius))));

    if(distance <= this->radius + radius2) {
        return true;
    } else {
        return false;
    }
}

