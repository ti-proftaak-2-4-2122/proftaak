//
// Test Template
// Created by twanh on 27-5-2022.
//

#include <iostream>

#include "utest.h"

#include "GameTimer.h"

TEST_CASE(gameTimerZeroAtStart) {

    assert(GameTimer::getCurrentTime() == 0.0);
    assert(GameTimer::getDeltaTime() == 0.0f);

    TEST_SUCCESS();
}

TEST_CASE(gameTimerReset) {

    // GameTimer must be 0 at start
    assert(GameTimer::getCurrentTime() == 0.0);
    assert(GameTimer::getDeltaTime() == 0.0f);

    // Reset Timer
    GameTimer::reset();

    // GameTimer must still be 0
    assert(GameTimer::getCurrentTime() == 0.0);
    assert(GameTimer::getDeltaTime() == 0.0f);

    // Update Timer
    GameTimer::update(1.0);

    // Check if timer has updated
    assert(GameTimer::getCurrentTime() == 1.0);
    assert(GameTimer::getDeltaTime() == 1.0f);

    // Reset Timer
    GameTimer::reset();

    // Check if timer has reset
    assert(GameTimer::getCurrentTime() == 0.0);
    assert(GameTimer::getDeltaTime() == 0.0f);

    TEST_SUCCESS();
}

TEST_CASE(gameTimerUpdate) {

    // Reset Timer
    GameTimer::reset();

    // Update timer
    GameTimer::update(2.0);

    // Check if timer has updated
    assert(GameTimer::getCurrentTime() == 2.0);
    assert(GameTimer::getDeltaTime() == 2.0f);

    // Update again
    GameTimer::update(3.0);

    // DeltaTime must be (3.0 - 2.0) = 1.0
    assert(GameTimer::getCurrentTime() == 3.0);
    assert(GameTimer::getDeltaTime() == 1.0f);

    TEST_SUCCESS();
}

TEST_CASE(gameTimerUpdateEqualToLastTime) {

    GameTimer::reset();

    // Update with 3.0, twice
    GameTimer::update(3.0);
    GameTimer::update(3.0);

    // DeltaTime must be 0.0, current time must be 3.0
    assert(GameTimer::getCurrentTime() == 3.0);
    assert(GameTimer::getDeltaTime() == 0.0f);

    TEST_SUCCESS();
}

TEST_CASE(gameTimerUpdateLessThanLastTime) {

    GameTimer::reset();

    // Update time to 3.0
    GameTimer::update(3.0);

    // Update time to 2.0, is less than last => should throw
    assert_exception(GameTimer::update(2.0));

    // Time should not have changed
    assert(GameTimer::getCurrentTime() == 3.0);
    assert(GameTimer::getDeltaTime() == 3.0f);

    TEST_SUCCESS();
}

TEST_CASE(gameTimerUpdateNegative) {

    GameTimer::reset();

    // Update time with 2.0
    GameTimer::update(2.0);

    // Update timer to -1.0
    assert_exception(GameTimer::update(-1.0));

    // Time should not have changed
    assert(GameTimer::getCurrentTime() == 2.0);
    assert(GameTimer::getDeltaTime() == 2.0f);

    TEST_SUCCESS();
}

TEST_CASE(gameTimerUpdateFraction) {

    GameTimer::reset();

    // Update with fraction
    GameTimer::update(0.125);

    // Time should be the same. Check range, because of float in-precision
    assert(GameTimer::getCurrentTime() == 0.125);
    assert(GameTimer::getDeltaTime() > 0.120f && GameTimer::getDeltaTime() < 0.130f);

    // Update with another fraction
    GameTimer::update(0.750);

    // Time should have updated. Check range, because of float in-precision
    assert(GameTimer::getCurrentTime() == 0.750);
    assert(GameTimer::getDeltaTime() > 0.620f && GameTimer::getDeltaTime() < 0.630f);

    TEST_SUCCESS();
}

TEST_MAIN() {

    RUN_TEST_CASE(gameTimerZeroAtStart);
    RUN_TEST_CASE(gameTimerReset);

    RUN_TEST_CASE(gameTimerUpdate);
    RUN_TEST_CASE(gameTimerUpdateEqualToLastTime);
    RUN_TEST_CASE(gameTimerUpdateLessThanLastTime);
    RUN_TEST_CASE(gameTimerUpdateNegative);
    RUN_TEST_CASE(gameTimerUpdateFraction);

    TEST_SUCCESS();
}