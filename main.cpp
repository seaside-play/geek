#include <iostream>
#include "src/c++17/demo.hpp"

int main(int argc, char** argv) {
    std::cout << "argc:" << argc << std::endl;
    for (int i = 0 ; i < argc; ++i) {
        std::cout << "param " << i << " " << argv[i] << std::endl;
    }

    cpp17::Demo cpp17_demo;
    cpp17_demo.Test();

    return 1;
}