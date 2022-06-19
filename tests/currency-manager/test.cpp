//
// Test Template
// Created by twanh on 27-5-2022.
//

#include "utest.h"
#include "CurrencyManager.h"
#include "GameTimer.h"

#define CreateDummyCurrencyManager() CurrencyManager currencyManager(2, 1.0f, 0.8f, 10.0f)

TEST_CASE(constructCurrencyManager) {

    CreateDummyCurrencyManager();

    // Test if there are two players created
    assert(currencyManager.getPlayerCurrency(0) != -1);
    assert(currencyManager.getPlayerCurrency(1) != -1);

    // Test if there are not more than two players created
    assert(currencyManager.getPlayerCurrency(2) == -1);

    // Test if start currency was applied
    assert(currencyManager.getPlayerCurrency(0) == 1.0f);
    assert(currencyManager.getPlayerCurrency(1) == 1.0f);

    // Test if currencyRate is correct
    assert(currencyManager.getCurrencyRate() == 0.8f);

    // Test if maxCurrency is correct
    assert(currencyManager.getMaxCurrency() == 10.0f);

    TEST_SUCCESS();
}

TEST_CASE(getPlayerOutOfBounds) {

    CreateDummyCurrencyManager();

    // Get negative player
    assert(currencyManager.getPlayerCurrency(-1) == -1);

    // Get player out of bounds
    assert(currencyManager.getPlayerCurrency(10) == -1);

    TEST_SUCCESS();
}

TEST_CASE(currencyManagerUpdate) {

    CreateDummyCurrencyManager();

    GameTimer::reset();

    // Check if start currency
    assert(currencyManager.getPlayerCurrency(0) == 1.0f);
    assert(currencyManager.getPlayerCurrency(1) == 1.0f);

    // Update by one second
    GameTimer::update(1.0);
    currencyManager.update();

    // Currency must have advanced with around currency rate
    assert(currencyManager.getPlayerCurrency(0) == 1.0f + currencyManager.getCurrencyRate());
    assert(currencyManager.getPlayerCurrency(1) == 1.0f + currencyManager.getCurrencyRate());

    // Update again
    GameTimer::update(1.5);
    currencyManager.update();

    // Currency must have advanced with around 1.5 currency rate
    assert_equals(currencyManager.getPlayerCurrency(0), 1.0f + currencyManager.getCurrencyRate() * 1.5f);
    assert_equals(currencyManager.getPlayerCurrency(1), 1.0f + currencyManager.getCurrencyRate() * 1.5f);

    TEST_SUCCESS();
}

TEST_CASE(updateOverMaxCurrency) {

    CreateDummyCurrencyManager();

    GameTimer::reset();

    // Check if start currency
    assert(currencyManager.getPlayerCurrency(0) == 1.0f);
    assert(currencyManager.getPlayerCurrency(1) == 1.0f);

    // Update by a long time
    GameTimer::update(100.0);
    currencyManager.update();

    // Currency must be max currency now
    assert_equals(currencyManager.getPlayerCurrency(0), currencyManager.getMaxCurrency());
    assert_equals(currencyManager.getPlayerCurrency(1), currencyManager.getMaxCurrency());

    TEST_SUCCESS();
}

TEST_CASE(setPlayerCurrency) {

    CreateDummyCurrencyManager();

    GameTimer::reset();

    // Check if start currency
    assert(currencyManager.getPlayerCurrency(0) == 1.0f);
    assert(currencyManager.getPlayerCurrency(1) == 1.0f);

    // Set currency
    currencyManager.setPlayerCurrency(0, 3.0f);
    currencyManager.setPlayerCurrency(1, 0.0f);

    // Check if currency has updated
    assert(currencyManager.getPlayerCurrency(0) == 3.0f);
    assert(currencyManager.getPlayerCurrency(1) == 0.0f);

    // Set currency to invalid values
    currencyManager.setPlayerCurrency(0, -3.0f);
    currencyManager.setPlayerCurrency(1, currencyManager.getMaxCurrency() * 3);

    // Check if currency has updated, within valid ranges
    assert(currencyManager.getPlayerCurrency(0) == 0.0f);
    assert(currencyManager.getPlayerCurrency(1) == currencyManager.getMaxCurrency());

    // Update out of bounds, should not throw and do nothing
    currencyManager.setPlayerCurrency(4, 5.0f);
    assert(currencyManager.getPlayerCurrency(4) == -1.0f);

    TEST_SUCCESS();
}

TEST_CASE(updateAndSetPlayerCurrency) {

    TEST_SUCCESS();
}

TEST_CASE(setProperties) {

    TEST_SUCCESS();
}

TEST_CASE(resetCurrencyManager) {

    TEST_SUCCESS();
}

TEST_MAIN() {

    RUN_TEST_CASE(constructCurrencyManager);

    RUN_TEST_CASE(getPlayerOutOfBounds);
    RUN_TEST_CASE(currencyManagerUpdate);
    RUN_TEST_CASE(updateOverMaxCurrency);
    RUN_TEST_CASE(setPlayerCurrency);
    RUN_TEST_CASE(updateAndSetPlayerCurrency);
    RUN_TEST_CASE(updateAndSetPlayerCurrency);
    RUN_TEST_CASE(setProperties);
    RUN_TEST_CASE(resetCurrencyManager);

    TEST_SUCCESS();
}