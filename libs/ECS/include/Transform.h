//
// Created by Daan van Donk on 10/05/2022.
//

#ifndef PROFTAAK24_TRANSFORM_H
#define PROFTAAK24_TRANSFORM_H

#include "Vector3.h"

struct Transform{
public:
    Vector3 position = Vector3(0, 0, 0);
    Vector3 rotation = Vector3(0, 0, 0);
    Vector3 scale = Vector3(0, 0, 0);
};
#endif //PROFTAAK24_TRANSFORM_H

