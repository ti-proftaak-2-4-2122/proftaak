//
// Created by Daan van Donk on 10/06/2022.
//

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include "Animator.h"
#include "GameTimer.h"
#include "ModelManager.h"

namespace fs = std::filesystem;
Animator::Animator(const std::string& folderName, Mesh& mesh, int fps) : mesh(mesh) {
    speedBetweenFrames = 1.0f/(float)fps;

    for (const auto & entry : fs::directory_iterator(folderName))
        frames.push_back(ModelManager::getModel(entry.path().string()));
}

void Animator::StartAnimation()
{
    isRunning = true;
}

void Animator::StopAnimation()
{
    isRunning = false;
}


void Animator::Update()
{
    Component::Update();

    currentTime += GameTimer::getDeltaTime();

    if(currentTime >= speedBetweenFrames) {
        currentTime = 0;
        NextFrame();
        mesh.SetMesh(frames[index]);
    }
}

void Animator::NextFrame() {
    if(index+1 > frames.size() - 1) {
        index = 0;
    } else {
        index++;
    }
}
