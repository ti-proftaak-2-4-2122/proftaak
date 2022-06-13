/**
 * @file
 * @brief Header file for the AIPrefab class
 * @author doguk
 * @date 24-05-2022
 */
#pragma once

#include "GameObject.h"
#include "Collider.h"
#include "CharacterStats.h"
#include "Mesh.h"
#include "LerpController.h"
#include "CombatController.h"
#include "map"

class CombatState;

class AIPrefab : public GameObject
{
private:

    typedef enum {
        TOP_LEFT_BRIDGE,
        TOP_RIGHT_BRIDGE,
        BOTTOM_LEFT_BRIDGE,
        BOTTOM_RIGHT_BRIDGE,
        TOWER_TOP_LEFT,
        TOWER_BOTTOM_LEFT,
        TOWER_TOP_RIGHT,
        TOWER_BOTTOM_RIGHT
    } AI_POSITION;

    bool IsTowerDestroyed = false;
    float currentTime;
    LerpController* lerpController;
    Collider* collider;
    CharacterStats* characterStats;
    CharacterStats* otherStats;
    std::vector<glm::vec3> checkPoints {};

    std::map<AI_POSITION, glm::vec3> predefinedPositions {{TOP_LEFT_BRIDGE,     glm::vec3(9.0f, 0.0f, -12.0f)},
                                                  {        BOTTOM_LEFT_BRIDGE,  glm::vec3(9.0f, 0.0f, 12.0f)},
                                                  {        TOP_RIGHT_BRIDGE,    glm::vec3(-9.0f, 0.0f, -12.0f)},
                                                  {        BOTTOM_RIGHT_BRIDGE, glm::vec3(-9.0f, 0.0f, 12.0f)},
                                                  {        TOWER_TOP_LEFT,      glm::vec3(-25.0f, 0.0f, -12.0f)},
                                                  {        TOWER_BOTTOM_LEFT,   glm::vec3(-25.0f, 0.0f, -12.0f)},
                                                  {        TOWER_TOP_RIGHT,     glm::vec3(25.0f, 0.0f, 12.0f)},
                                                  {        TOWER_BOTTOM_RIGHT,  glm::vec3(25.0f, 0.0f, 12.0f)}};

    void StartCombat(CharacterStats* otherStats);
    void DoDamage();
    void StopCombat();
    void InitStats(UnitTypeEnum type);

    void InitCheckpoints();

public:

    //Combat logic
    bool IsAttacking = false;
    bool hasFought = false;
    bool hasSpawnedTop = true;

    AIPrefab(Transform* transform, UnitTypeEnum type, bool hasSpawnedTop);

    void onTriggerEnter(Collider* other) override;
    void onTriggerExit(Collider* other) override;
    void Update() override;
};
