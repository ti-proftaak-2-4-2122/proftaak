/**
 * @file
 * @brief CurrencyDisplayPrefab
 * @author twanh
 * @date 15-6-2022
 */

#pragma once

#include "GameObject.h"

class StrGuiComponent;

class CurrencyDisplayPrefab : public GameObject
{
private:
    StrGuiComponent* player1StrGuiComponent = nullptr;
    StrGuiComponent* player2StrGuiComponent = nullptr;

public:
    CurrencyDisplayPrefab();
    void Update() override;
};
