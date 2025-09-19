#pragma once
#include <iostream>

namespace AbstractFactory
{
// 抽象产品
class ProductA {
public:
    virtual void Use() = 0;
    virtual ~ProductA() = default;
};

// 具体产品
class ConcreteProductA1 : public ProductA {
public:
    void Use() override
    {
        std::cout << "Using ConcreteProductA1" << std::endl;
    }
};

class ConcreteProductA2 : public ProductA {
public:
    void Use() override
    {
        std::cout << "Using ConcreteProductA2" << std::endl;
    }
};

// 抽象产品
class ProductB {
public:
    virtual void Use() = 0;
    virtual ~ProductB() = default;
};

// 具体产品
class ConcreteProductB1 : public ProductB {
public:
    void Use() override
    {
        std::cout << "Using ConcreteProductB1" << std::endl;
    }
};

class ConcreteProductB2 : public ProductB {
public:
    void Use() override
    {
        std::cout << "Using ConcreteProductB2" << std::endl;
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
        std::cout << "Creator  destruct" << std::endl;
    }
    virtual ProductA *CreateProductA() = 0;
    virtual ProductB *CreateProductB() = 0;
};

/**
 * @brief 由于基类为纯虚基类，所以子类必须对接口进行实现，
 * 所以子类必须生产所有抽象产品且每个抽象产品只能生产一种
 *
 */
class ConcreteCreatorA : public Creator {
public:
    ConcreteCreatorA()
    {
        std::cout << "ConcreteCreatorA construct" << std::endl;
    }
    virtual ~ConcreteCreatorA()
    {
        std::cout << "ConcreteCreatorA destruct" << std::endl;
    }
    ProductA *CreateProductA() override
    {
        std::cout << "create ConcreteCreatorA1" << std::endl;
        return new ConcreteProductA1();
    }

    ProductB *CreateProductB() override
    {
        std::cout << "create ConcreteCreatorB1" << std::endl;
        return new ConcreteProductB1();
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
        std::cout << "ConcreteCreatorB destruct" << std::endl;
    }
    ProductA *CreateProductA() override
    {
        std::cout << "create ConcreteCreatorA2" << std::endl;
        return new ConcreteProductA2();
    }

    ProductB *CreateProductB() override
    {
        std::cout << "create ConcreteCreatorB2" << std::endl;
        return new ConcreteProductB2();
    }
};

} // namespace AbstractFactory

/**
 * @brief 抽象工厂模式测试，抽象工厂中的一个工厂可以生产多种产品
 *
 */
void AbstractFactoryTest()
{
    AbstractFactory::Creator *factory1 = new AbstractFactory::ConcreteCreatorA();
    AbstractFactory::ProductA *product_a1 = factory1->CreateProductA();
    AbstractFactory::ProductB *product_b1 = factory1->CreateProductB();
    product_a1->Use();
    product_b1->Use();

    AbstractFactory::Creator *factory2 = new AbstractFactory::ConcreteCreatorB();
    AbstractFactory::ProductA *product_a2 = factory2->CreateProductA();
    AbstractFactory::ProductB *product_b2 = factory2->CreateProductB();
    product_a2->Use();
    product_b2->Use();

    delete factory1;
    delete factory2;
    delete product_a1;
    delete product_b1;
    delete product_a2;
    delete product_b2;
}
