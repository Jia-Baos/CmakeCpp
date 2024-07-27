/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief Cpp临时项目
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>

#include "../../3rdparty/FMT/include/fmt/color.h"
#include "../../3rdparty/FMT/include/fmt/core.h"
#include "./MyException.hpp"
#include "./TypeShow.hpp"
#include "./APIDesign.hpp"
#include "./DesignPattern.hpp"
#include "./MySpan.hpp"

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  os << "{";
  for (size_t i = 0; i < v.size(); ++i) {
    os << v[i];
    if (i != v.size() - 1) {
      os << ", ";
    }
  }

  os << "}";
  return os;
}

int main(int argc, char *argv[]) {
  fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic, "{}\n", "Welcome to fmt");

  auto t0 = std::chrono::steady_clock::now();

  std::vector<int> v = {4, 3, 2, 1, 0, -1, -2};
  std::cout << v << std::endl;

  const int val = 10;
  using type = decltype(val);

  SHOW(int const &);

  test_foo();
  test_insert();
  test_span();
  test_optional();
  test_enum0();
  test_enum1();
  test_enum2();

  // test_reduce0();
  // test_reduce1();
  // test_reduce2();
  test_reduce3();

  demo_span();

  std::this_thread::sleep_for(std::chrono::milliseconds(3));  // 跨平台延时函数

  auto t1 = std::chrono::steady_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
  std::cout << "time elapsed: " << time << " ms" << std::endl;
  return 0;
}
