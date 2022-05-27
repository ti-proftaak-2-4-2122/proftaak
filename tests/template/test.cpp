//
// Test Template
// Created by twanh on 27-5-2022.
//

#include "utest.h"

TEST_CASE(demoTest) {
    if(false)
        TEST_FAILED("You suck at coding! (But now in test case!)");

    TEST_SUCCESS();
}

TEST_MAIN() {

    if(false)
        TEST_FAILED("You suck at coding!");

    RUN_TEST_CASE(demoTest);

    TEST_SUCCESS();

}