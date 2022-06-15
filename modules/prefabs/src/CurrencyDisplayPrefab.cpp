/**
 * @file
 * @brief CurrencyDisplayPrefab
 * @author twanh
 * @date 15-6-2022
 */

#include <string>
#include <sstream>
#include <iomanip>

#include "gui/StrGuiComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "glm/glm.hpp"

#include "CurrencyDisplayPrefab.h"

CurrencyDisplayPrefab::CurrencyDisplayPrefab() : GameObject()
{
    this->player1StrGuiComponent = new StrGuiComponent("Green Goop: 0.0");
    this->player1StrGuiComponent->setScale({0.7f, 0.7f, 0.7f});
    this->player1StrGuiComponent->setPosition({ -1.0, 0.95 });

    this->player2StrGuiComponent = new StrGuiComponent("Green Goop: 0.0");
    this->player2StrGuiComponent->setScale({0.7f, 0.7f, 0.7f});
    this->player2StrGuiComponent->setPosition({ 0.56, 0.95 });

    GameObject::AddComponent(this->player1StrGuiComponent);
    GameObject::AddComponent(this->player2StrGuiComponent);
}

void CurrencyDisplayPrefab::Update()
{
    GameObject::Update();

    std::stringstream player1Stream;
    player1Stream << "Green Goop: "
        << std::fixed << std::setprecision(1) << Scene::getSingleton().getCurrencyManager().getPlayerCurrency(0);

    std::stringstream player2Stream;
    player2Stream << "Green Goop: "
        << std::fixed << std::setprecision(1) << Scene::getSingleton().getCurrencyManager().getPlayerCurrency(1);

    this->player1StrGuiComponent->setText(player1Stream.str());
    this->player2StrGuiComponent->setText(player1Stream.str());
}