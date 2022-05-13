//
// Created by Daan van Donk on 10/05/2022.
//

#ifndef PROFTAAK24_TRANSFORM_H
#define PROFTAAK24_TRANSFORM_H

#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>

class Transform : public Component
{
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};
#endif //PROFTAAK24_TRANSFORM_H

