#pragma optimize( "", on )

#include <iostream>
#include <filesystem>
#include <fstream>
#include "tests.h"
#include "graph.h"

namespace fs = std::filesystem;

void runTests(){
    TestRunner tr;
    tr.RunTest(TestNS::TestDate, "TestDate");
    tr.RunTest(TestNS::TestGraph, "TestGraph");
}

int main(int argc, char* argv[]) {
    int exitcode = 0;
    // runTests();
    try {
        fs::path p = fs::current_path();
        std::cout << "Current path: " << p << std::endl;
        std::cout << "Enter path to file with data:\n>>>  ";
        std::string filename;
        std::cin >> filename;
        std::fstream file;
        file.open(filename, std::ios::in);
        if (!file.is_open())
            throw std::runtime_error(
                    "Failed to open file " + filename
            );
        else
            std::cout << "Opened successfully\n";
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
        std::string inputline;
        std::cout << "Enter start and final points:" << std::endl;
        while(true){
            int first, second;
            std::cin >> first;
            if (std::cin.peek() == ',') std::cin.ignore();
            std::cin >> second;
            graph.search(first, second, true);
        }
    }
    catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        exitcode = -1;
    }
    std::cin.get();
    return exitcode;
}
