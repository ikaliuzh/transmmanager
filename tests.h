#pragma once

#include "test_runner.h"
#include "date.h"

// test date
namespace TestNS {
    void TestDate() {
        Date x(1, 59, 59);
        Date y(0, 0, 1);
        ASSERT_EQUAL(x + y, Date(2, 0, 0))
        ASSERT(x >= y)
        ASSERT(!(x < y))
        ASSERT(x != y)
        ASSERT(x - y == Date(1, 59, 58))
        std::stringstream ss;
        ss << "20:17:30" << std::endl;
        Date z;
        ss >> z;
        ASSERT_EQUAL(z, Date(20, 17, 30))
    }

}