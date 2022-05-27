//
// Test Template
// Created by twanh on 27-5-2022.
//

#include <iostream>

#include "utest.h"

#include "GameTimer.h"

TEST_CASE(deltaTimeZeroAtStart) {

    assert(GameTimer::deltatime == 0.0f);

    TEST_SUCCESS();
}

TEST_CASE(deltaTimeUpdate) {

    // GameTimer::deltaTime must still be 0
    assert(GameTimer::deltatime == 0.0f);

    // Update timer
    GameTimer::update(2.0);

    // Check if timer has updated
    assert(GameTimer::deltatime == 2.0f);

    // Update again
    GameTimer::update(3.0);

    // DeltaTime must be (3.0 - 2.0) = 1.0
    assert(GameTimer::deltatime == 1.0f);

    TEST_SUCCESS();
}

TEST_CASE(deltaTimeUpdateEqualToLastTime) {

    // GameTimer::deltaTime must be 1.0 (from previous test)
    assert(GameTimer::deltatime == 1.0f);

    // Update with last time (is 3.0, in previous test)
    GameTimer::update(3.0);

    // DeltaTime must be 0.0
    assert(GameTimer::deltatime == 0.0f);

    TEST_SUCCESS();
}

TEST_CASE(deltaTimeUpdateLessThanLastTime) {

    // GameTimer::deltaTime must be 0.0 (from previous test)
    assert(GameTimer::deltatime == 0.0f);

    // Update deltaTime with 2.0, is less than last
    assert_exception(GameTimer::update(2.0));

    // deltaTime should not have changed
    assert(GameTimer::deltatime == 0.0f);

    TEST_SUCCESS();
}

TEST_CASE(deltaTimeUpdateNegative) {

    // GameTimer::deltaTime must be 0.0 (from previous test)
    assert(GameTimer::deltatime == 0.0f);

    // Update deltaTime with -1.0
    assert_exception(GameTimer::update(-1.0));

    // deltaTime should not have changed
    assert(GameTimer::deltatime == 0.0f);

    TEST_SUCCESS();
}

TEST_MAIN() {

    RUN_TEST_CASE(deltaTimeZeroAtStart);

    RUN_TEST_CASE(deltaTimeUpdate);
    RUN_TEST_CASE(deltaTimeUpdateEqualToLastTime);
    RUN_TEST_CASE(deltaTimeUpdateLessThanLastTime);
    RUN_TEST_CASE(deltaTimeUpdateNegative);

    TEST_SUCCESS();
}