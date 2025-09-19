#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <limits>

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

struct MinReducer : Reducer {
    int Init() override
    {
        return std::numeric_limits<int>::max();
    }

    int Add(int a, int b) override
    {
        return std::min(a, b);
    }
};

struct MaxReducer : Reducer {
    int Init() override
    {
        return std::numeric_limits<int>::min();
    }

    int Add(int a, int b) override
    {
        return std::max(a, b);
    }
};

int Reduce(const std::vector<int> &v, const std::shared_ptr<Reducer> &reducer)
{
    int res = reducer->Init();
    for (int i = 0; i < v.size(); i++) {
        res = reducer->Add(res, v[i]);
    }
    return res;
}

struct MoveStrategy {
public:
    void Run() {}
    void Move() {}
};

struct AttackStrategy {
public:
    void Attack() {}
};

struct Character {
    std::shared_ptr<MoveStrategy> move_strategy;
    std::shared_ptr<AttackStrategy> attack_strategy;

    void Update()
    {
        if (true) {
            move_strategy->Move();
        } else if (true) {
            move_strategy->Run();
        }
        while (true) {
            attack_strategy->Attack();
        }
    }
};

void StrategyTest()
{
    std::cout << "StrategyTest()" << std::endl;
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::cout << "  SumReducer, res is: " << Reduce(v, std::make_shared<SumReducer>()) << std::endl;         // 等价于之前的 sum(v)
    std::cout << "  ProductReducer, res is: " << Reduce(v, std::make_shared<ProductReducer>()) << std::endl; // 等价于之前的 product(v)
    std::cout << "  MinReducer, res is: " << Reduce(v, std::make_shared<MinReducer>()) << std::endl;         // 等价于之前的 product(v)
    std::cout << "  MaxReducer, res is: " << Reduce(v, std::make_shared<MaxReducer>()) << std::endl;         // 等价于之前的 product(v)
}
