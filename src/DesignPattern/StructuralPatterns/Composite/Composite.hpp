#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

// Component接口
class Component {
public:
    virtual void Operation() const = 0; // 业务操作
    virtual ~Component() = default;     // 虚析构函数
};

// Leaf类，表示叶子节点
class Leaf : public Component {
public:
    void Operation() const override
    {
        std::cout << "Leaf operation" << std::endl;
    }
};

// Composite类，表示复合节点
class Composite : public Component {
private:
    std::vector<std::shared_ptr<Component>> m_children_; // 子节点

public:
    // 添加子组件
    void Add(const std::shared_ptr<Component> &component)
    {
        m_children_.push_back(component);
    }

    // 删除子组件
    void Remove(const std::shared_ptr<Component> &component)
    {
        // for (auto iter = m_children.begin(); iter != m_children.end(); ++iter) {
        //     if (*iter == component) {
        //         m_children.erase(iter);
        //     }
        // }
        m_children_.erase(std::remove(m_children_.begin(), m_children_.end(), component), m_children_.end());
    }

    void Operation() const override
    {
        std::cout << "Composite operation" << std::endl;
        for (const auto &child : m_children_) {
            child->Operation(); // 遍历 vector 调用子组件的operation
        }
    }
};

// Client代码
void CompositeTest()
{
    std::shared_ptr<Component> leaf1 = std::make_shared<Leaf>();
    std::shared_ptr<Component> leaf2 = std::make_shared<Leaf>();

    std::shared_ptr<Composite> composite = std::make_shared<Composite>();
    composite->Add(leaf1);
    composite->Add(leaf2);

    std::cout << "Client calls operation on composite:" << std::endl;
    composite->Operation(); // 输出Composite operation -> Leaf operation -> Leaf operation
}
