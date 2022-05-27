//
// Created by twanh on 27-5-2022.
//

#pragma once

#include <iostream>
#include <stdexcept>

#include "test_exception.h"
#include "test_case_exception.h"

#define TEST_SUCCESS() return 0
#define TEST_FAILED(message) throw utest::test_exception( \
    message,                                              \
    std::string(__FILE__) + ":" + std::to_string(__LINE__)\
)

#define TEST_MAIN(code) int main() \
{ \
    try { \
        code; \
        TEST_SUCCESS(); \
    } \
    catch(utest::test_case_exception& ex) { \
        std::cerr << "Test case that failed: " << ex.caseName << std::endl \
        << "Test fail reason: " << ex.innerException.message << std::endl \
        << "Test fail location: " << ex.innerException.location << std::endl; \
        return 1; \
    } \
    catch(utest::test_exception& ex) { \
        std::cerr << "Test fail reason: " << ex.message << std::endl \
        << "Test fail location: " << ex.location << std::endl;       \
        return 1; \
    } \
}

#define RUN_TEST_CASE(caseName) caseName ()

#define TEST_CASE(caseName, code) int caseName () { \
    try { \
        code; \
        TEST_SUCCESS(); \
    } \
    catch(utest::test_exception& ex) { \
        throw utest::test_case_exception(std::string(#caseName), ex); \
    } \
    TEST_SUCCESS(); \
}

// EOF