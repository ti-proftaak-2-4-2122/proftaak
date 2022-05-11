//
// Created by Daan van Donk on 11/05/2022.
//

#ifndef PROFTAAK24_LERPCONTROLLER_H
#define PROFTAAK24_LERPCONTROLLER_H

#include "Vector3.h"
#include "Component.h"

class LerpController : public Component
{
public:
    void Move(Vector3 startPos, Vector3 endPos, float speed);
    void Awake() override;
    void Update() override;
};


#endif //PROFTAAK24_LERPCONTROLLER_H
