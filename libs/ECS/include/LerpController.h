//
// Created by Daan van Donk on 11/05/2022.
//

#ifndef PROFTAAK24_LERPCONTROLLER_H
#define PROFTAAK24_LERPCONTROLLER_H

#include "Component.h"
#include <glm/fwd.hpp>

class LerpController : public Component
{
public:
    void Move(glm::vec3 startPos, glm::vec3 endPos, float speed);
    void Awake() override;
    void Update() override;
};


#endif //PROFTAAK24_LERPCONTROLLER_H
