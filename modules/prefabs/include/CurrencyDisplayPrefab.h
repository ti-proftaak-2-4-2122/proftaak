/**
 * @file
 * @brief CurrencyDisplayPrefab
 * @author twanh
 * @date 15-6-2022
 */

#pragma once

#include "GameObject.h"

class StrGuiComponent;

/**
 * @class Prefab that displays the Currency (Green Goop) on the screen
 * This is for both players.
 * Uses the @StrGuiComponent to draw the data onto the screen
 */
class CurrencyDisplayPrefab : public GameObject
{
private:
    StrGuiComponent* player1StrGuiComponent = nullptr;
    StrGuiComponent* player2StrGuiComponent = nullptr;

public:
    /**
     * @brief Sets the data of currency with a certain colour to be displayed
     */
    CurrencyDisplayPrefab();

    /**
     * @brief Updates the currency counter and displays it on screen.
     */
    void Update() override;
};
