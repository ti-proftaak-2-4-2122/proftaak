//
// Created by twanh on 27-5-2022.
//

#pragma once

#include <stdexcept>
#include <string>

namespace utest
{

    class test_exception : std::exception
    {
    public:
        std::string message;
        std::string location;

        test_exception(std::string message, std::string location);
    };

}
