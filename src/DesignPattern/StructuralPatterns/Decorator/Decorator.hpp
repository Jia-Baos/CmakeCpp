#pragma once
#include <iostream>

namespace Decorator
{

/**
 * @brief  抽象组件接口
 *
 */

class Component {
public:
    virtual void Operation() = 0;
    virtual ~Component() = default;
};

/**
 * @brief 具体组件类
 *
 */
class ConcreteComponent : public Component {
public:
    void Operation() override
    {
        std::cout << "ConcreteComponent operation" << std::endl;
    }
};

/**
 * @brief 定义装饰者类的抽象基类，其实现 Component 接口
 *
 */
class Decorator : public Component {
public:
    Decorator(Component *component)
        : m_component(component) {}

    void Operation()
    {
        m_component->Operation();
    }

protected:
    Component *m_component; // 子类要能够访问
};

/**
 * @brief 具体装饰者类A
 *
 */
class ConcreteDecoratorA : public Decorator {
public:
    // 调用父类的构造函数
    ConcreteDecoratorA(Component *component)
        : Decorator(component) {}

    void Operation()
    {
        std::cout << "ConcreteDecoratorA operation" << std::endl;
        m_component->Operation(); // 递归调用 component 的operation
    }
};

/**
 * @brief 具体装饰者类B
 *
 */
class ConcreteDecoratorB : public Decorator {
public:
    // 调用父类的构造函数
    ConcreteDecoratorB(Component *component)
        : Decorator(component) {}

    void Operation()
    {
        std::cout << "ConcreteDecoratorB operation" << std::endl;
        m_component->Operation(); // 递归调用 component 的operation
    }
};

} // namespace Decorator

void DecoratorTest()
{
    Decorator::Component *component = new Decorator::ConcreteComponent();
    component = new Decorator::ConcreteDecoratorA(component);
    component = new Decorator::ConcreteDecoratorB(component);
    component->Operation();
    delete component;
}
