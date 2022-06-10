//
// Created by Ewout on 1-6-2022.
//

#pragma once

#include "Component.h"
#include "glad/glad.h"
#include "glm/ext/matrix_transform.hpp"


class GameObject;

class Gui : public GameObject
{

public:
    Gui();

    GLuint fontTxId;
};