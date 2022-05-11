//
// Created by Daan van Donk on 11/05/2022.
//

#include <iostream>
#include "LerpController.h"
void LerpController::Move(Vector3 startPos, Vector3 endPos, float speed) {

}

void LerpController::Awake() {
    std::cout << "Testing Awake of LerpController" << std::endl;
}

void LerpController::Update() {
    std::cout << "Moving" << std::endl;
}
