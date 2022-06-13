//
// Created by tjtle on 01/06/2022.
//

#pragma once

#include "Component.h"
#include "CardDetector.h"
#include <map>
#include "GameObject.h"
#include "Scene.h"
#include "Transform.h"
#include "Mesh.h"
#include "ModelManager.h"
#include "glm/ext/matrix_projection.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include <windows.h>

class Spawner : public Component
{
public:
    void UpdateAfterDraw() override;
    void Awake() override;

private:
    CardDetector *detector = CardDetector::GetInstance();
    std::map<unsigned int, GameObject*> spawnedObjects;
    std::vector<CardDetector::Card> receivedCards;

    bool HasCard(unsigned int color);


    static glm::vec3 ConvertCords(CardDetector::Card card);
};
