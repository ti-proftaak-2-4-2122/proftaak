//
// Created by twanh on 10-6-2022.
//

#pragma once

#include <vector>

class CurrencyManager
{
private:
    std::vector<float> playerWalletList;

    float startCurrency;
    float currencyRate;
    float maxCurrency;

public:
    CurrencyManager(int playerCount, float startCurrency, float currencyRate, float maxCurrency);

    void update();

    void reset(float startCurrency = -1);

    float getPlayerCurrency(int player);
    void setPlayerCurrency(int player, float currency);

    [[nodiscard]] float getCurrencyRate() const;
    void setCurrencyRate(float currencyRate);

    [[nodiscard]] float getMaxCurrency() const;
    void setMaxCurrency(float maxCurrency);

};
