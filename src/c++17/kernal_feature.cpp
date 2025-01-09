#include "kernal_feature.hpp"

#include <string>
#include <iostream>

namespace cpp17 {

void KernalFeature::Test() {
  std::cout << __func__ << std::endl;
  TestStructureBind();
}

void KernalFeature::TestStructureBind() {
  struct MyStruct {
    int i;
    std::string s;
  };

  MyStruct ms {1, "Chris"};
  auto [u, v] {ms};
  std::cout << "u:" << u << " v:" << v << std::endl;

  auto fn_get_struct = []() {
    return MyStruct{42, "hello"};
  };

  auto [id, val] = fn_get_struct();
  std::cout << "id:" << id << " val:" << val << std::endl;

  const auto & [u1, v1] = ms;
  std::cout << "u1:" << u1 << " v1:" << v1 << std::endl;

  ms.i = 100;
  ms.s = "Peter";
  std::cout << "u1:" << u1 << " v1:" << v1 << std::endl;

  // test move
  MyStruct ms2 = { 42, "Jim" };
  // v 和 n 指向的匿名实体是 ms 的右值引用，同时 ms 仍持有值
  auto&& [v2, n2] = std::move(ms2);
  std::cout << "v2:" << v2 << " n2:" << n2 << " ms2.i:" << ms2.i << " ms2.s:" << ms2.s << std::endl;
}

} // namespace cpp17