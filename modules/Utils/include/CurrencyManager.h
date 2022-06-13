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
    /**
     * @brief Default constructor for the CurrencyManager
     * @param playerCount The amount of players
     * @param startCurrency The start currency. Every player will have this amount on initialisation or when resetting.
     * @param currencyRate The currency rate in currency amount per second.
     * @param maxCurrency The maximum amount of currency every individual player may have.
     *                      Currency amount for a player will never be higher than this value
     */
    CurrencyManager(int playerCount, float startCurrency, float currencyRate, float maxCurrency);

    /**
     * @brief Will update the currency of each player based on the delta time between the previous call to this function and the currency rate.
     */
    void update();

    /**
     * @brief Resets every players currency to the specified start currency.
     * @param startCurrency The start currency for every player.
     * If not specified or -1, will use the start currency that was provided in the constructor.
     */
    void reset(float startCurrency = -1);

    /**
     * @brief Gets the current currency amount for the specified player.
     * @param player The player index.
     * @return The current currency amount for the player.
     */
    [[nodiscard]] float getPlayerCurrency(int player);

    /**
     * @brief Sets the current currency amount for the specified player.
     * @param player The player index.
     * @param currency The new currency amount for the player.
     *                  Will be bound between 0 and maxCurrency.
     */
    void setPlayerCurrency(int player, float currency);

    /**
     * @brief Updates the current currency amount for the specified player with an specific delta.
     * @param player The player index.
     * @param delta The delta currency amount. May be positive or negative.
     *                  The new currency amount will be bound between 0 and maxCurrency.
     */
    void updatePlayerCurrency(int player, float delta);

    /**
     * @brief Ensures a player has a specified amount of currency
     * @param player The player index.
     * @param amount The amount of currency a player must have.
     * @return True if the player has enough currency, false if it doesn't have enough currency.
     */
    bool requirePlayerCurrency(int player, float amount);

    /**
     * @brief Gets the current currency rate.
     * @return The current currency rate.
     */
    [[nodiscard]] float getCurrencyRate() const;

    /**
     * @brief Sets the current currency rate.
     * @param currencyRate The new currency rate.
     */
    void setCurrencyRate(float currencyRate);

    /**
     * @brief Gets the current max currency.
     * @return The current max currency.
     */
    [[nodiscard]] float getMaxCurrency() const;

    /**
     * @brief Sets the current max currency.
     * @param currencyRate The new max currency.
     */
    void setMaxCurrency(float maxCurrency);

};
