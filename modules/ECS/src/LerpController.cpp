//
// Created by Daan van Donk on 11/05/2022.
//

#include <iostream>
#include "LerpController.h"
#include "glm/vec3.hpp"

void LerpController::Move(glm::vec3 startPos, glm::vec3 endPos, float speed) {

}

void LerpController::Awake() {
    std::cout << "Testing Awake of LerpController" << std::endl;
}

void LerpController::Update() {
    std::cout << "Moving" << std::endl;
}
