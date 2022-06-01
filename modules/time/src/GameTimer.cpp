/**
 * @file
 * @brief Source file for the GameTimer class
 * @author Ewout
 * @date 24-05-2022
 */

#include "GameTimer.h"

void GameTimer::update(double time)
{
    deltatime = (float)(time - lastTime);
    lastTime = time;
}
