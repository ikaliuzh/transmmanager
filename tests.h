#pragma once

#include "test_runner.h"
#include "graph.h"
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

    void TestGraph() {
        std::string input = "1181,1902,1937,131.34,4:50:00,15:52:00\n"
                      "1163,1902,1981,131.84,4:37:00,15:52:00\n"
                      "1137,1902,1937,131.34,19:53:00,8:21:00\n"
                      "1311,1981,1937,192.33,7:08:00,19:06:00\n"
                      "1349,1981,1929,284.84,14:35:00,13:57:00\n";
        std::stringstream ss; ss << input;
        Graph graph;
        Transmission tr;
        int i = 5;
        while (i--){
            ss >> tr;
            graph.insert(tr.id, tr);
        }
        std::vector<std::vector<int>> ans {{1181}, {1137}};
        ASSERT_EQUAL(ans , graph.search(1902, 1937, false));
        std::vector<std::vector<int>> ans2 {{1181}, {1137}};
        ASSERT_EQUAL(ans2 , graph.search(1902, 2020, false));
    }
}