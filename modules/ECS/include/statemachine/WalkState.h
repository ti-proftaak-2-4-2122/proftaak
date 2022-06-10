/**
 * @file
 * @brief Header file for the WalkState class
 * @author doguk
 * @date 24-05-2022
 */

#pragma once
#include "statemachine/State.h"

class State;

class WalkState: public State
{
public:

    WalkState(AIContext* aiContext);

    void actionSwitched() override;
};
