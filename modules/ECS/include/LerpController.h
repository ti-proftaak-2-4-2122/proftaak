//
// Created by Daan van Donk on 11/05/2022.
//

#ifndef PROFTAAK24_LERPCONTROLLER_H
#define PROFTAAK24_LERPCONTROLLER_H

#include "Component.h"
#include "glm/glm.hpp"

class GameObject;
class Component;
class LerpController : public Component
{
public:
    void Move(glm::vec3 startPos, glm::vec3 endPos, float speed);
    void Update() override;
    LerpController();

private:
    glm::vec3 slope;
    int stepAmount;
    int stepCount;
};


#endif //PROFTAAK24_LERPCONTROLLER_H
