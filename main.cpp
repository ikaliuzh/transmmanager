#pragma optimize( "", on )

#include <iostream>
#include <fstream>
#include "tests.h"
#include "graph.h"

void runTests(){
    TestRunner tr;
    tr.RunTest(TestNS::TestDate, "TestDate");
    tr.RunTest(TestNS::TestGraph, "TestGraph");
}

int main(int argc, char* argv[]) {
    //runTests();
    try {
        std::string filename = "C:/Users/kaluz/CLionProjects/transmissionmanager/data.csv";
        std::fstream file;
        file.open(filename, std::ios::in);
        if (!file.is_open())
            throw std::runtime_error(
                    "Failed to open file " + filename
            );
        Graph graph;
        std::string line;
        getline(file, line);
        while (getline(file, line)) {
            std::stringstream ss;
            ss << line;
            Transmission tr;
            ss >> tr;
            graph.insert(tr.id, tr);
        }
        graph.search(1902, 1937, true);
    }
    catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return -1;
    }
    std::cin.get();
    return 0;
}
