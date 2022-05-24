//
// Created by doguk on 5/24/2022.
//
#include "../include/AIPrefab.h"

AIPrefab::AIPrefab()
{
    context = new AIContext();
}

void AIPrefab::onTriggerEnter()
{
    context->switchState(new CombatState(context));
}
