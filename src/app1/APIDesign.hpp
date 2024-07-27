/**
 * @file APIDesign.hpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief
 * @version 0.1
 * @date 2024-05-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma
#ifndef APIDESIGN_HPP
#define APIDESIGN_HPP

#include <iostream>
#include <vector>
#include <map>
#include <span>
#include <optional>
#include <string>

/* 结构体传参 */

struct FooOptions {
  std::string name;
  int age;
  int phone;
  int address;
};

void foo(FooOptions opts) { std::cout << "good design..." << std::endl; };

void foo(std::string name, int age, int phone, int address) { std::cout << "bad design..." << std::endl; };

void test_foo() {
  foo({.name = "小彭老师", .age = 24, .phone = 12345, .address = 67890});
  foo(/*name=*/"小彭老师", /*age=*/24, /*phone=*/12345, /*address=*/67890);
}

/* 结构体作为返回值 */
// template <typename T>
// struct insert_result_t {
//   bool success;
//   std::map<T>::iterator position;
// };

// template <typename K, typename V>
// struct map_entry_t {
//   K key;
//   V value;
// };

// insert_result_t insert(map_entry_t<int, int> entry) { std::cout << " struct as the return value" << std::endl; };

void test_insert() {
  std::map<std::string, std::string> map_t{};

  const auto [it0, success0] = map_t.insert({"hello0", "world0"});
  std::cout << "insert success: " << success0 << std::endl;
  std::cout << "insert position: " << std::distance(it0, map_t.begin()) << std::endl;

  // const auto [it1, success1] = map_t.insert({"hello1", "world1"});
  // std::cout << "insert success: " << success1 << std::endl;
  // std::cout << "insert position: " << std::distance(it1, map_t.begin()) << std::endl;
}

/* 胖指针 Span
 * 应用场景
 * 作为函数的参数，用于指示函数需要处理的数据范围；
 * 作为类的成员变量，用于表示对象所管理的内存区域；
 * 作为数组的视图，用于访问数组的一部分
 *
 */
void test_span() {
  int a[] = {0, 1, 2};
  std::span<int> mySpan(a);

  std::span<int>::difference_type distance = mySpan.end() - mySpan.begin();
  std::cout << "span size: " << distance - 1 << std::endl;
}

/* std::optional */
// optional can be used as the return type of a factory that may fail
std::optional<std::string> create0(bool b) {
  if (b) return "Godzilla";
  return std::nullopt;
}

// std::nullopt can be used to create any (empty) std::optional
auto create1(bool b) { return b ? std::optional<std::string>{"Godzilla"} : std::nullopt; }

void test_optional() {
  std::cout << "create(false) returned " << create0(false).value_or("empty") << std::endl;

  // optional-returning factory functions are usable as conditions of while and if
  if (auto str = create1(true)) {
    std::cout << "create2(true) returned " << str.value() << std::endl;
  }
}

/* enum */

enum class Sex0 {
  Female = 0,
  Male = 1,
  Custom = 2,
};

void test_enum0() { std::cout << "sex is: " << (int)Sex0::Male << std::endl; };

enum class Sex1 : uint8_t {
  Female = 0,
  Male = 1,
  Custom = 2,
};

void test_enum1() {
  static_assert(sizeof(Sex1) == 1);
  std::cout << "sex size: " << sizeof(Sex1) << std::endl;
};

enum class Age : int {};
enum class Phone : int {};

template <class T>
  requires std::is_enum_v<T>
T operator+(T a, T b) {
  using U = std::underlying_type_t<T>;
  return T((U)a + (U)b);
}

void foo(Age age, Phone phone) { std::cout << "age is: " << (int)age << ", phone is: " << (int)phone << std::endl; };

void test_enum2() {
  foo(Age(42), Phone(12345));
  std::cout << "Age(42) + Age(42) = " << (int)(Age(42) + Age(42)) << std::endl;
}

#endif  //! APIDESIGN_HPP