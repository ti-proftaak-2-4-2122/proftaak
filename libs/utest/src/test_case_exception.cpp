//
// Created by twanh on 27-5-2022.
//

#include "utest.h"

namespace utest
{
    test_case_exception::test_case_exception(
            std::string caseName,
            utest::test_exception innerException
        )
        : caseName(caseName), innerException(innerException)
    {

    }

} // utest