/**
 * @file Span.hpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief Demo about Span (C++20)
 * @version 0.1
 * @date 2024-05-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma
#ifndef MYSPAN_HPP
#define MYSPAN_HPP

#include <iostream>

void demo_span() {
  int a[] = {0, 1, 2};
  std::span<int> my_span(a);

  std::cout << my_span.back() << std::endl;
}

#endif  // !MYSPAN_HPP