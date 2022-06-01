//
// Created by Ewout on 24-5-2022.
//

#include "GameTimer.h"

void GameTimer::update(double time)
{
    deltatime = (float)(time - lastTime);
    lastTime = time;
}
