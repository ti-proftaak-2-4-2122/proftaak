//
// Created by robin on 20-May-22.
//

#include <iostream>
#include "Collider.h"
#include "Transform.h"

void Collider::CheckColliders(const std::vector<Collider *> &other){

    for (const auto collider : other){
        if (this == collider) continue;
        if (CheckCollision(*collider))
        {

           // std::cout << "Collided with object\n";
            //        attack.onTriggerEnter(other);
        }

    }
}


Collider::Collider(float radius) : radius(radius) {
    std::cout << "Collision created radius: " << radius <<"\n";
}

bool Collider::CheckCollision(Collider &other)
{


    // get center point circle first

    auto position = this->gameObject->transform.getPosition();
    auto positionOther = this->gameObject->transform.getPosition();

    glm::vec2 positionFlat = {position.x,position.z};
    glm::vec2 positionOtherFlat = {positionOther.x, positionOther.z};

    // get center point circle first
    glm::vec2 center(positionFlat + radius);
    glm::vec2 center_other(positionOtherFlat + 1.0f);

    // get difference vector between both centers
    glm::vec2 difference = center - center_other;

    std::cout << "glm lenght diffrence: "<<glm::length(difference)<<"\n";

    return glm::length(difference) < this->radius;



    //return glm::length(difference) < one.Radius;
}


