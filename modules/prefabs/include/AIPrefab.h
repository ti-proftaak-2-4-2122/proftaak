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
#include "gui/StrGuiComponent.h"
#include "LerpController.h"
#include "map"

/**
 * @class Prefab that will enact the behaviour of a unit
 */
class AIPrefab : public GameObject
{
private:

    /**
     * @brief All possible positions Tags within the play field
     */
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

    bool isLerpINTR = false;
    float currentTime;
    int wayPointIndex = 0;

    LerpController* lerpController;
    Collider* collider;
    CharacterStats* characterStats;
    CharacterStats* otherStats;
    StrGuiComponent *strGuiComponent;
    std::vector<glm::vec3> checkPoints {};

    /**
     * @brief all possible positions that a unit can walk through/have
     */
    std::map<AI_POSITION, glm::vec3> predefinedPositions {{TOP_LEFT_BRIDGE,     glm::vec3(-9.0f, 0.0f, -12.0f)},
                                                  {        BOTTOM_LEFT_BRIDGE,  glm::vec3(-9.0f, 0.0f, 12.0f)},
                                                  {        TOP_RIGHT_BRIDGE,    glm::vec3(9.0f, 0.0f, -12.0f)},
                                                  {        BOTTOM_RIGHT_BRIDGE, glm::vec3(9.0f, 0.0f, 12.0f)},
                                                  {        TOWER_TOP_LEFT,      glm::vec3(-25.0f, 0.0f, -12.0f)},
                                                  {        TOWER_BOTTOM_LEFT,   glm::vec3(-25.0f, 0.0f, 12.0f)},
                                                  {        TOWER_TOP_RIGHT,     glm::vec3(25.0f, 0.0f, -12.0f)},
                                                  {        TOWER_BOTTOM_RIGHT,  glm::vec3(25.0f, 0.0f, 12.0f)}};

    /**
     * @brief based on the response of @OnTriggerEnter will start attacking the other Prefab,
     * based on which collision occurred be it a unit or tower.
     * @param otherStats The stats of the other Prefab.
     */
    void StartCombat(CharacterStats* otherStats);
    void DoDamage();
    void StopCombat();

    /**
     * @brief Initializes stats based on which unit type has defined in @Spawner
     * @param type
     */
    void InitStats(UnitTypeEnum type);

    /**
     * @brief Based on where on playing field a unit is spawned,
     * setup the list of checkpoints that it needs to follow.
     */
    void InitCheckpoints();

public:

    bool IsAttacking = false;

    AIPrefab(Transform* transform, UnitTypeEnum type);

    bool setLerpINTR(const bool& newLerpINTR);

    /**
     * @brief When collision occurs this function to handle the behaviour,
     * based on what the prefab collided with.
     * @param other collider that this prefab encountered
     */
    void onTriggerEnter(Collider* other) override;

    /**
     * @brief if no collision is detected this function is called and the current behaviour continues.
     * @param other the other collider that it no longer detects.
     */
    void onTriggerExit(Collider* other) override;

    /**
     * @brief Updates all variables that handle certain behaviours
     * Such as: walking, checking if we are able to walk, attacking,
     * displaying health to screen.
     */
    void Update() override;
};
