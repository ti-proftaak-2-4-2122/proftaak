//
// Created by Daan van Donk on 10/05/2022.
//

#ifndef PROFTAAK24_TRANSFORM_H
#define PROFTAAK24_TRANSFORM_H

#include "Component.h"
#include "glm/glm.hpp"
class GameObject;

class Transform : public Component
{

public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    Transform(GameObject *gameObject);
};
#endif //PROFTAAK24_TRANSFORM_H

