/**
 * @file
 * @brief Source file for the GameTimer class
 * @author Ewout
 * @date 24-05-2022
 */

#include <stdexcept>
#include "GameTimer.h"

void GameTimer::update(double time)
{
    if(time < 0)
        throw std::invalid_argument("time is not allowed to be negative");

    if(time < GameTimer::currentTime)
    {
        throw std::invalid_argument("time is not allowed to be set to a smaller value than the "
                                    "previous update time");
    }

    GameTimer::deltaTime = (float)(time - GameTimer::currentTime);
    GameTimer::currentTime = time;
}

void GameTimer::reset() {
    GameTimer::currentTime = 0.0;
    GameTimer::deltaTime = 0.0f;
}

double GameTimer::getCurrentTime() {
    return GameTimer::currentTime;
}

float GameTimer::getDeltaTime() {
    return GameTimer::deltaTime;
}