//
// Created by Daan van Donk on 10/06/2022.
//

#ifndef PROFTAAK24_ANIMATOR_H
#define PROFTAAK24_ANIMATOR_H


#include "Component.h"
#include "ObjModel.h"
#include "Mesh.h"

class Mesh;

class Animator : public Component
{
private:
    std::vector<ObjModel*> frames;
    float speedBetweenFrames = 1;
    bool isRunning = false;

    float currentTime = 0;
    int index = 0;

    Mesh& mesh;

    void NextFrame();
public:
    Animator(std::string folderName, Mesh& mesh);

    void StartAnimation();
    void StopAnimation();

    void Update() override;
};


#endif //PROFTAAK24_ANIMATOR_H
