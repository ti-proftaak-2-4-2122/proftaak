//
// Created by robin on 20-May-22.
//

#include "Collider.h"
#include "Transform.h"

void Collider::CheckColliders(const std::vector<Collider *> &other){

    for (const auto collider : other){
        if (CheckCollision(*collider))
        {
            //        attack.onTriggerEnter(other);
        }

    }

}


Collider::Collider(float radius) : radius(radius) {

}

bool Collider::CheckCollision(Collider &other)
{
    // get center point circle first

    auto position = this->gameObject->transform.getPosition();
    auto positionOther = this->gameObject->transform.getPosition();

    // get center point circle first
    glm::vec2 center(position + radius);
    glm::vec2 center_other(positionOther + 1.0f);

    // get difference vector between both centers
    glm::vec2 difference = center - center_other;

    return glm::length(difference) < this->radius;



    //return glm::length(difference) < one.Radius;
}


