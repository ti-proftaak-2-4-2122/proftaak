/**
 * @file
 * @brief Header file for the Collider class
 * @author Daan van Donk
 * @date 24-05-2022
 */

#pragma once

#include "Component.h"
#include "glm/glm.hpp"
#include <vector>

/**
 * @brief Collider is a component within the ECS that checks collision,
 * for themselves and others around them albeit a unit or tower
 */
class Collider : public Component
{
public:
    float radius;

    /**
     * @brief Basic constructor that sets the collider based on the incoming radius
     * @param radius gotten from @CharacterStats
     */
    Collider(float radius);

    /**
     * @brief Checks collision from themselves to other objects,
     * Calculates distance between itself and the other object (hence the name Collider *other)
     * @param other
     */
    void CheckCollision(Collider* other);

    /**
     * @brief Update loop that checks if itself is a collider then skips over it,
     * else calls the @CheckCollision function
     */
    void Update() override;

    /**
     * @brief If a GameObject has been destroyed/defeated then this function cleans it's own collider
     * @param collider current collider that needs to be deleted out of the vector @otherColliders.
     */
    static void CleanUp(Collider* collider);

    /**
     * @brief Adds colliders from GameObjects that are within the Scene to @otherColliders
     * @param collider is the current GameObject collider that needs to be added to @othercolliders.
     */
    static void addCollider(Collider* collider);

private:
    bool hasEntered = true;
    inline static std::vector<Collider*> otherColliders;

};
