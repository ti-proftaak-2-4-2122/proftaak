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
    void Update() override;
    void Draw() override;
    void Spawn();
private:

    int greenPoolIndex = 0;
    std::vector<GameObject*> greenPreviewPool;

    int redPoolIndex = 0;
    std::vector<GameObject*> redPreviewPool;

    int yellowPoolIndex = 0;
    std::vector<GameObject*> yellowPreviewPool;

    CardDetector *detector = CardDetector::GetInstance();
    std::vector<CardDetector::Card> receivedCards;

    bool HasCard(unsigned int color);

    static glm::vec3 ConvertCords(CardDetector::Card& card);

    GameObject* getPreviewGameObjectForCard(const CardDetector::Card& card);

    void updatePreviewList(const std::vector<GameObject*>& previewPool, const int& usedCount);
    void drawPreviewList(const std::vector<GameObject*>& previewPool, const int& usedCount);
};
