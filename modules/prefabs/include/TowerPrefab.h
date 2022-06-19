//
// Created by doguk on 5/27/2022.
//

#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "CharacterStats.h"
#include "Mesh.h"
#include "gui/StrGuiComponent.h"

class GameObject;

/**
 * @class TowerPrefab which is the objective of AIPrefabs to destroy.
 * In the ~TowerPrefab() a ref count is updated to check if all towers on one side have been destroyed.
 * If that is the case trigger the win condition.
 */
class TowerPrefab : public GameObject
{
public:
    explicit TowerPrefab(Transform *transform, std::string name);
    ~TowerPrefab();

    /**
     * @brief Initializes the @characterStats team, to not prevent infighting on the same team.
     */
    void InitTowerTeam();

    /**
     * @brief if this tower collides with a unit start the predefined behaviour for this prefab
     * @param other is a unit of the other team that it collided with.
     */
    void onTriggerEnter(Collider* other) override;

    /**
     * @brief if there is no collision exit the behaviour,
     * to then continue the idle behaviour
     * @param other collider that no longer exists.
     */
    void onTriggerExit(Collider* other) override;

    /**
     * @brief Updates data such as health with @strGuiComponent,
     * Attacking behaviour gets checked.
     */
    void Update() override;

private:

    bool IsAttacking = false;
    float currentTime;

    Collider* collider;
    CharacterStats* characterStats;
    CharacterStats* otherStats;
    StrGuiComponent *strGuiComponent;

    /**
     * @brief Combat behaviour
     * @param otherStats is the unit that it collided with in @OnTriggerEnter,
     * this unit is of the other team and not of the same team.
     */
    void StartCombat(CharacterStats* otherStats);
    void StopCombat();
    void DoDamage();
};


