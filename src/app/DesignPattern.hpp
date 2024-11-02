/**
 * @file DesignPattern.hpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief Demo about design pattern
 * @version 0.1
 * @date 2024-05-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma
#ifndef DESIGNPATTERN_HPP
#define DESIGNPATTERN_HPP

#include <iostream>
#include <vector>
#include <numeric>
#include <optional>

/* 策略模式 */
struct Reducer {
  virtual int init() = 0;
  virtual int add(int a, int b) = 0;
};

struct SumReducer : Reducer {
  int init() override { return 0; }

  int add(int a, int b) override { return a + b; }
};

struct ProductReducer : Reducer {
  int init() override { return 1; }

  int add(int a, int b) override { return a * b; }
};

int reduce(const std::vector<int>& v, Reducer* reducer) {
  int res = reducer->init();
  for (int i = 0; i < v.size(); i++) {
    res = reducer->add(res, v[i]);
  }
  return res;
}

struct MinReducer : Reducer {
  int init() override { return std::numeric_limits<int>::max(); }

  int add(int a, int b) override { return std::min(a, b); }
};

struct MaxReducer : Reducer {
  int init() override { return std::numeric_limits<int>::min(); }

  int add(int a, int b) override { return std::max(a, b); }
};

void test_reduce0() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::cout << "SumReducer, res is: " << reduce(v, new SumReducer()) << std::endl;          // 等价于之前的 sum(v)
  std::cout << "ProductReducer, res is: " << reduce(v, new ProductReducer()) << std::endl;  // 等价于之前的 product(v)
  std::cout << "MinReducer, res is: " << reduce(v, new MinReducer()) << std::endl;  // 等价于之前的 product(v)
  std::cout << "MaxReducer, res is: " << reduce(v, new MaxReducer()) << std::endl;  // 等价于之前的 product(v)
}

/* 迭代器模式 */
struct Inputer {
  virtual std::optional<int> fetch() = 0;
};

struct CinInputer : Inputer {
  std::optional<int> fetch() override {
    int tmp;
    std::cin >> tmp;
    if (tmp == -1) return std::nullopt;
    return tmp;
  }
};

struct VectorInputer : Inputer {
  std::vector<int> v;
  int pos = 0;

  VectorInputer(std::vector<int> v) : v(v) {}

  std::optional<int> fetch() override {
    if (pos == v.size()) return std::nullopt;
    return v[pos++];
  }
};

int reduce(Inputer* inputer, Reducer* reducer) {
  int res = reducer->init();
  while (auto opt = inputer->fetch()) {
    int tmp = opt.value();
    res = reducer->add(res, tmp);
  }

  return res;
}

void test_reduce1() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::cout << "SumReducer, res is: " << reduce(new VectorInputer(v), new SumReducer()) << std::endl;
  std::cout << "SumReducer, res is: " << reduce(new CinInputer(), new SumReducer()) << std::endl;
}

/* 适配器模式 */
struct StopInputerAdapter : Inputer {
  Inputer* inputer;
  int stopMark;

  StopInputerAdapter(Inputer* inputer, int stopMark) : inputer(inputer), stopMark(stopMark) {}

  std::optional<int> fetch() override {
    auto tmp = inputer->fetch();
    if (tmp == stopMark) return std::nullopt;
    return tmp;
  }
};

void test_reduce2() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, -1, 9, 0};

  std::cout << "SumReducer, res is: " << reduce(new StopInputerAdapter(new VectorInputer(v), -1), new SumReducer())
            << std::endl;  // 从 vector 读到 -1 为止
  std::cout << "SumReducer, res is: " << reduce(new StopInputerAdapter(new CinInputer(), -1), new SumReducer())
            << std::endl;  // 从 cin 读到 -1 为止
}

struct FilterStrategy {
  virtual bool shouldPass(int value) = 0;  // 返回 true 表示该值应该被丢弃
};

struct FilterStrategyAbove : FilterStrategy {  // 大于一定值（threshold）才能通过
  int threshold;

  FilterStrategyAbove(int threshold) : threshold(threshold) {}

  bool shouldPass(int value) override { return value > threshold; }
};

struct FilterStrategyBelow : FilterStrategy {  // 小于一定值（threshold）才能通过
  int threshold;

  FilterStrategyBelow(int threshold) : threshold(threshold) {}

  bool shouldPass(int value) override { return value < threshold; }
};

struct FilterStrategyAnd : FilterStrategy {  // 要求 a 和 b 两个过滤策略都为 true，才能通过
  FilterStrategy* a;
  FilterStrategy* b;

  FilterStrategyAnd(FilterStrategy* a, FilterStrategy* b) : a(a), b(b) {}

  bool shouldPass(int value) override { return a->shouldPass(value) && b->shouldPass(value); }
};

struct FilterInputerAdapter : Inputer {
  Inputer* inputer;
  FilterStrategy* strategy;

  FilterInputerAdapter(Inputer* inputer, FilterStrategy* strategy) : inputer(inputer), strategy(strategy) {}

  std::optional<int> fetch() override {
    while (true) {
      auto tmp = inputer->fetch();
      if (!tmp.has_value()) {
        return std::nullopt;
      }
      if (strategy->shouldPass(tmp.value())) {
        return tmp;
      }
    }
  }
};

void test_reduce3() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, -1, 9, 0};

  std::cout << "SumReducer, res is: "
            << reduce(new FilterInputerAdapter(
                          new StopInputerAdapter(new VectorInputer(v), -1),
                          new FilterStrategyAnd(new FilterStrategyAbove(3), new FilterStrategyBelow(5))),
                      new SumReducer())
            << std::endl;  // 从 vector 读到 -1 为止
}

#endif  // !DESIGNPATTERN_HPP