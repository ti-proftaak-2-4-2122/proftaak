/**
 * @file
 * @brief TeamHelper
 * @author twanh
 * @date 15-6-2022
 */

#pragma once

#include "Transform.h"
#include "glm/gtc/type_ptr.hpp"

class TeamHelper
{
public:
    static short getTeamByTransform(const Transform& transform);
    static short getTeamByPosition(const glm::vec3& position);
};
