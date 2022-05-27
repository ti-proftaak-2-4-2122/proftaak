//
// Created by twanh on 27-5-2022.
//

#pragma once

#include <iostream>
#include <stdexcept>

#include "test_exception.h"

#define TEST_SUCCESS() return 0
#define TEST_FAILED(message) throw utest::test_exception( \
    message,                                              \
    std::string(__FILE__) + ":" + std::to_string(__LINE__)\
)

#define TEST_MAIN(code) int main() \
{ \
    try { \
        code \
        TEST_SUCCESS(); \
    } \
    catch(utest::test_exception& ex) { \
        std::cerr << "Test fail reason: " << ex.message << std::endl \
        << "Test fail location: " << ex.location << std::endl;       \
        return 1; \
    } \
}

// EOF