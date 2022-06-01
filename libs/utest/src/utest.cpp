//
// Created by twanh on 27-5-2022.
//

#include "utest.h"

namespace utest {

    int run(std::string caseName, int (*test_func)(void)) {

        try {
            test_func();
            TEST_SUCCESS();
        }
        catch(utest::test_exception& ex) {
            // Test has failed
            throw utest::test_case_exception(caseName, ex);
        }

        TEST_SUCCESS();
    }

}