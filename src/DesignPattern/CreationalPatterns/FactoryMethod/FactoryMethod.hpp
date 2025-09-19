#pragma once
#include <iostream>

namespace FactoryMethod
{
// 抽象产品接口
class Product {
public:
    virtual void Use() = 0;
    virtual ~Product() = default;
};

// 具体产品 A
class ConcreteProductA : public Product {
public:
    void Use() override
    {
        std::cout << "Using ConcreteProductA" << std::endl;
    }
};

// 具体产品 B
class ConcreteProductB : public Product {
public:
    void Use() override
    {
        std::cout << "Using ConcreteProductB" << std::endl;
    }
};

/**
 * @brief 抽象建造者需要保有抽象产品的指针
 * 或者能够返回抽象产品的指针
 *
 */
class Creator {
public:
    Creator()
    {
        std::cout << "Creator  construct" << std::endl;
    }
    virtual ~Creator()
    {
        std::cout << "Creator  destroy" << std::endl;
    }
    virtual Product *FactoryMethod() = 0;
};

class ConcreteCreatorA : public Creator {
public:
    ConcreteCreatorA()
    {
        std::cout << "ConcreteCreatorA construct" << std::endl;
    }
    virtual ~ConcreteCreatorA()
    {
        std::cout << "ConcreteCreatorA destroy" << std::endl;
    }
    Product *FactoryMethod() override
    {
        std::cout << "create ConcreteCreatorA" << std::endl;
        return new ConcreteProductA();
    }
};

class ConcreteCreatorB : public Creator {
public:
    ConcreteCreatorB()
    {
        std::cout << "ConcreteCreatorB construct" << std::endl;
    }
    virtual ~ConcreteCreatorB()
    {
        std::cout << "ConcreteCreatorB destroy" << std::endl;
    }
    Product *FactoryMethod() override
    {
        std::cout << "create ConcreteCreatorB" << std::endl;

        return new ConcreteProductB();
    }
};

} // namespace FactoryMethod

/**
 * @brief 工厂方法模式测试，工厂方法中的一个工厂只可以生产一种产品
 *
 */
void FactoryMethodTest()
{
    FactoryMethod::Creator *creator1 = new FactoryMethod::ConcreteCreatorA();
    auto product1 = creator1->FactoryMethod();
    product1->Use();

    FactoryMethod::Creator *creator2 = new FactoryMethod::ConcreteCreatorB();
    auto product2 = creator2->FactoryMethod();
    product2->Use();

    delete product1;
    delete product2;
    delete creator1;
    delete creator2;
}
