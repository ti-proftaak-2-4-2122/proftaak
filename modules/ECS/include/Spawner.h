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

/**
 * @class Spawner that spawns Prefabs such as @AIPrefab and @TowerPrefab
 * The Spawn location is based on the position that is projected from OpenCV Coords to OpenGL coords
 * To preview the location where the prefab will be spawned, there are 3 previewPools
 * @greenPreviewPool, @redPreviewpool, @yellowPreviewPool, Based on the colour of the card (green, red, yellow),
 *
 */
class Spawner : public Component
{
private:

    int greenPoolIndex = 0;
    std::vector<GameObject*> greenPreviewPool;

    int redPoolIndex = 0;
    std::vector<GameObject*> redPreviewPool;

    int yellowPoolIndex = 0;
    std::vector<GameObject*> yellowPreviewPool;

    CardDetector *detector = CardDetector::GetInstance(); //Gets Reference of the current CardDetector.
    std::vector<CardDetector::Card> receivedCards;

    /**
     * @brief Checks if the card exists within the list of cards.
     * @param color of the card that is being checked
     * @return true if card colour exists
     */
    bool HasCard(unsigned int color);

    /**
     * @brief Converts the OpenCV Coords to OpenGL Coords.
     * @param card The card for .
     * @return Converted coords to be projected onto screen.
     */
    static glm::vec3 ConvertCords(CardDetector::Card& card);

    /**
     * @brief Gets the Game Object mesh preview based on the card colour
     * @param card is the card that has been detected within OpenCV
     */
    GameObject* getPreviewGameObjectForCard(const CardDetector::Card& card);

    /**
     * @brief Updates the current List to be the updated
     * @param previewPool isn the pool of meshes that are to be drawn
     * @param usedCount How many times a mesh has been used
     */
    void updatePreviewList(const std::vector<GameObject*>& previewPool, const int& usedCount);
    void drawPreviewList(const std::vector<GameObject*>& previewPool, const int& usedCount);

public:
    /**
     * @brief Overrides see @Component for explanation
     */
    void UpdateAfterDraw() override;
    void Awake() override;
    void Update() override;
    void Draw() override;
    void Spawn();
};
