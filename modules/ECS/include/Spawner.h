//
// Created by tjtle on 01/06/2022.
//

#pragma once

#include "Component.h"
#include "CardDetector.h"

class Spawner : public Component
{
private:

    CardDetector *detector = CardDetector::GetInstance();


};
