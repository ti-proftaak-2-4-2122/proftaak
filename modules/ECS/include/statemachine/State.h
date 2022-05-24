//
// Created by doguk on 5/24/2022.
//

#ifndef PROFTAAK24_STATE_H
#define PROFTAAK24_STATE_H
#include "AIContext.h"

class AIContext;

class State
{
public:
    AIContext* context;

    State(AIContext* context);

    virtual void actionSwitched() {};
};


#endif //PROFTAAK24_STATE_H
