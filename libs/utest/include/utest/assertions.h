//
// Created by twanh on 27-5-2022.
//

#pragma once

#include <stdexcept>

#include "utest.h"

/**
 * Success when true
 */
#define assert(exp) if (!(exp)) { TEST_FAILED(#exp " is false"); }

/**
 * Success when false
 */
#define assert_false(exp) if (exp) { TEST_FAILED(#exp " is true"); }

/**
 * Success when null
 */
#define assert_null(obj) if(obj != nullptr) { TEST_FAILED(#obj " is not null"); }

/**
 * Success when not null
 */
#define assert_not_null(obj) if(obj == nullptr) { TEST_FAILED(#obj " is null"); }

/**
 * Success when an exception is thrown
 */
#define assert_exception(code) try { \
    code;                            \
    TEST_FAILED(#code " should have thrown"); \
} catch (std::exception& ex) {}

// EOF