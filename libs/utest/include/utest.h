//
// Created by twanh on 27-5-2022.
//

#pragma once

#include <iostream>

#define TEST_SUCCESS() return 0
#define TEST_FAILED(message) { \
    std::cerr << "Test fail reason: " << message << std::endl \
    << "Test fail location: " << __FILE__ << ":" << __LINE__ << std::endl; \
    return 1; \
}