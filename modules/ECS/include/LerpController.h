/**
 * @file
 * @brief Header file for the LerpController class
 * @author Daan van Donk
 * @date 11-05-2022
 */

#pragma once

#include "Component.h"
#include "glm/glm.hpp"

class GameObject;

class Component;

/**
 * @class Calculates movement between the GameObject's current position to it's end position
 * Part of the Component hierarchy
 */
class LerpController : public Component
{
private:
    glm::vec3 endPos;
    glm::vec3 startPos;
    float fraction = 0.0f;
    const float roundValue = 1.0f;

public:
    /**
     * @brief Inits the values for calculation of the slope/lerp
     * @param startPos Is the gameObject current position
     * @param endPos Is the gameObject's destination.
     * @param speed Is how fast the GameObject can move, this is derived from @CharactersStats
     */
    void Move(glm::vec3 startPos, glm::vec3 endPos, float speed);

    /**
     * @brief Updates the lerp within glm based on a fraction
     */
    void Update() override;

    LerpController();

    /**
     * @brief Checks if the distance between the start- and endpos is not zero
     * (a.k.a. the GameObject having reached it's destination)
     * @param currentPos GameObjects current position
     * @param resultPos GameObjects destination
     * @return if distance is not 0 return true
     */
    bool CheckPos(glm::vec3 currentPos, glm::vec3 resultPos) const;

};