/**
 * @file
 * @brief TeamHelper
 * @author twanh
 * @date 15-6-2022
 */

#include "TeamHelper.h"

short TeamHelper::getTeamByTransform(const Transform &transform)
{
    return TeamHelper::getTeamByPosition(transform.getPosition());
}

short TeamHelper::getTeamByPosition(const glm::vec3& pos)
{
    if (pos.x <= 0) // Left side => Team 0
        return 0;
    else if (pos.x > 0) // Right side => Team 1
        return 1;

    return -1; // Should never be reached
}
