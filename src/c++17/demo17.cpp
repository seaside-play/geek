#include "demo17.hpp"

#include <iostream>

namespace cpp17 {

void Demo17::Test() {
  TestKernalFeature();
  std::cout << "Hello CPP17\n";
}

void Demo17::TestKernalFeature() {
  kernal_feature_.Test();
}

} // namespace cpp17