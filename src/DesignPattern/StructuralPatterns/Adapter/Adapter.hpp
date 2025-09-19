#pragma once
#include <optional>
#include <vector>
#include <iostream>

namespace Adapter
{
/**
 * @brief 策略模式，用来改变对象的行为
 *
 */
struct Reducer {
    virtual int Init() = 0;
    virtual int Add(int a, int b) = 0;
};

struct SumReducer : Reducer {
    int Init() override
    {
        return 0;
    }
    int Add(int a, int b) override
    {
        return a + b;
    }
};

struct ProductReducer : Reducer {
    int Init() override
    {
        return 1;
    }
    int Add(int a, int b) override
    {
        return a * b;
    }
};

/**
 * @brief 迭代器模式，用来处理输入
 *
 */
struct Inputer {
    virtual std::optional<int> fetch() = 0;
};

struct CinInputer : Inputer {
    std::optional<int> fetch() override
    {
        int tmp;
        std::cin >> tmp;

        if (tmp == -1)
            return std::nullopt;
        return tmp;
    }
};

struct VectorInputer : Inputer {
    std::vector<int> v;
    VectorInputer(std::vector<int> v)
        : v(v) {}

    int pos = 0;
    std::optional<int> fetch() override
    {
        if (pos == v.size())
            return std::nullopt;
        return v[pos++];
    }
};

/**
 * @brief 适配器模式
 *
 */
struct StopInputerAdapter : Inputer {
    Inputer *inputer;
    int stop_mark;

    StopInputerAdapter(Inputer *inputer, int stopMark)
        : inputer(inputer), stop_mark(stopMark) {}

    std::optional<int> fetch() override
    {
        auto tmp = inputer->fetch();
        if (tmp == stop_mark)
            return std::nullopt;
        return tmp;
    }
};

struct FilterStrategy {
    virtual bool ShouldPass(int value) = 0; // 返回 true 表示该值应该被丢弃
};

struct FilterStrategyAbove : FilterStrategy { // 大于一定值（threshold）才能通过
    int threshold;

    FilterStrategyAbove(int threshold)
        : threshold(threshold) {}
    bool ShouldPass(int value) override
    {
        return value > threshold;
    }
};

struct FilterStrategyBelow : FilterStrategy { // 小于一定值（threshold）才能通过
    int threshold;

    FilterStrategyBelow(int threshold)
        : threshold(threshold) {}
    bool ShouldPass(int value) override
    {
        return value < threshold;
    }
};

struct FilterStrategyAnd : FilterStrategy { // 要求 a 和 b 两个过滤策略都为 true，才能通过
    FilterStrategy *a;
    FilterStrategy *b;

    FilterStrategyAnd(FilterStrategy *a, FilterStrategy *b)
        : a(a), b(b) {}
    bool ShouldPass(int value) override
    {
        return a->ShouldPass(value) && b->ShouldPass(value);
    }
};

struct FilterInputerAdapter : Inputer {
    Inputer *inputer;
    FilterStrategy *strategy;

    FilterInputerAdapter(Inputer *inputer, FilterStrategy *strategy)
        : inputer(inputer), strategy(strategy) {}

    std::optional<int> fetch() override
    {
        while (true) {
            auto tmp = inputer->fetch();
            if (!tmp.has_value()) {
                return std::nullopt;
            }
            if (strategy->ShouldPass(tmp.value())) {
                return tmp;
            }
        }
    }
};

int Reduce(Inputer *inputer, Reducer *reducer)
{
    int res = reducer->Init();
    while (auto opt = inputer->fetch()) {
        int tmp = opt.value();
        res = reducer->Add(res, tmp);
    }

    return res;
}

} // namespace Adapter

void AdapterTest1()
{
    std::cout << "AdapterTest1()" << std::endl;
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, -1, 9, 0 };

    std::cout << "  SumReducer, res is: "
              << Reduce(new Adapter::StopInputerAdapter(new Adapter::VectorInputer(v), -1), new Adapter::SumReducer())
              << std::endl; // 从 vector 读到 -1 为止
    // std::cout << "SumReducer, res is: " << reduce(new StopInputerAdapter(new CinInputer(), -1), new SumReducer())
    //           << std::endl;  // 从 cin 读到 -1 为止
}

void AdapterTest2()
{
    std::cout << "AdapterTest2()" << std::endl;
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, -1, 9, 0 };

    std::cout << "  SumReducer, res is: "
              << Reduce(new Adapter::FilterInputerAdapter(
                            new Adapter::StopInputerAdapter(new Adapter::VectorInputer(v), -1),
                            new Adapter::FilterStrategyAnd(new Adapter::FilterStrategyAbove(3),
                                                           new Adapter::FilterStrategyBelow(5))),
                        new Adapter::SumReducer())
              << std::endl; // 从 vector 读到 -1 为止
}
