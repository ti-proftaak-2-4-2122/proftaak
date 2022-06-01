//
// Created by twanh on 27-5-2022.
//

#pragma once

#include <stdexcept>
#include <string>

#include "test_exception.h"

namespace utest
{

    class test_case_exception : public std::exception
    {
    public:
        std::string caseName;
        test_exception innerException;

        test_case_exception(std::string caseName, test_exception innerException);
    };

} // utest
