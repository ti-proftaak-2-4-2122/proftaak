//
// Created by Ewout on 13-5-2022.
//

#include "Transform.h"

Transform::Transform(GameObject *parentGameObject) : Component(parentGameObject) {
    position = glm::vec3(0,0,0);
    rotation = glm::vec3(0,0,0);
    scale = glm::vec3(0,0,0);

}
