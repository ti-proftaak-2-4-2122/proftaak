//
// Created by twanh on 10-6-2022.
//

#include <vector>

#include "GameTimer.h"

#include "CurrencyManager.h"

CurrencyManager::CurrencyManager(int playerCount, float startCurrency, float currencyRate, float maxCurrency)
    : playerWalletList(std::vector<float>(playerCount, startCurrency)),
      startCurrency(startCurrency),
      currencyRate(currencyRate),
      maxCurrency(maxCurrency)
{

}

void CurrencyManager::update()
{
    for(float& playerWalletValue : this->playerWalletList)
    {
        if(playerWalletValue >= this->maxCurrency)
            continue;

        playerWalletValue = std::min(
                playerWalletValue + (GameTimer::getDeltaTime() * this->currencyRate),
                this->maxCurrency
        );
    }
}

void CurrencyManager::reset(float startCurrency)
{
    if(startCurrency < 0)
        startCurrency = this->startCurrency;
    else
        this->startCurrency = startCurrency;

    for(float& playerWalletValue : this->playerWalletList)
        playerWalletValue = startCurrency;

}

float CurrencyManager::getPlayerCurrency(int player)
{
    float result = -1;

    if(player >= 0 && player < this->playerWalletList.size())
        result = this->playerWalletList[player];

    return result;
}

void CurrencyManager::setPlayerCurrency(int player, float currency)
{
    if(player >= 0 && player < this->playerWalletList.size())
        this->playerWalletList[player] = std::min(std::max(0.0f, currency), this->maxCurrency);;
}

void CurrencyManager::updatePlayerCurrency(int player, float delta)
{
    this->setPlayerCurrency(player, this->getPlayerCurrency(player) + delta);
}

bool CurrencyManager::requirePlayerCurrency(int player, float amount)
{
    return this->getPlayerCurrency(player) >= amount;
}

float CurrencyManager::getCurrencyRate() const
{
    return this->currencyRate;
}

void CurrencyManager::setCurrencyRate(float currencyRate)
{
    this->currencyRate = currencyRate;
}

float CurrencyManager::getMaxCurrency() const
{
    return this->maxCurrency;
}

void CurrencyManager::setMaxCurrency(float maxCurrency)
{
    this->maxCurrency = maxCurrency;
}