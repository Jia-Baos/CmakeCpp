#pragma once
#include <vector>
#include <iostream>
#include <optional>
#include <memory>

namespace Iterator
{
/* 策略模式 */
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

/* 迭代器模式 */
struct Inputer {
    virtual std::optional<int> Fetch() = 0;
};

struct CinInputer : Inputer {
    std::optional<int> Fetch() override
    {
        int tmp;
        std::cin >> tmp;
        if (tmp == -1)
            return std::nullopt;
        return tmp;
    }
};

struct VectorInputer : Inputer {

    VectorInputer(std::vector<int> v)
        : v(v) {}

    std::optional<int> Fetch() override
    {
        if (pos == v.size())
            return std::nullopt;
        return v[pos++];
    }

    int pos = 0;
    std::vector<int> v;
};

int Reduce(const std::shared_ptr<Inputer> &inputer, const std::shared_ptr<Reducer> &reducer)
{
    int res = reducer->Init();
    while (auto opt = inputer->Fetch()) {
        int tmp = opt.value();
        res = reducer->Add(res, tmp);
    }

    return res;
}

} // namespace Iterator

void IteratorTest()
{
    std::cout << "IteratorTest()" << std::endl;
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::cout << "  SumReducer, res is: " << Reduce(std::make_shared<Iterator::VectorInputer>(v), std::make_shared<Iterator::SumReducer>()) << std::endl;
    // std::cout << "SumReducer, res is: " << reduce(new CinInputer(), new SumReducer()) << std::endl;
}
