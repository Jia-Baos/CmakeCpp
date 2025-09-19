#pragma once
#include <vector>
#include <iostream>
#include <memory>

// 前向声明
class Book;
class Magazine;
class ConcreteVisitor;

// 访问者接口
class Visitor {
public:
    virtual void Visit(Book &book) = 0;
    virtual void Visit(Magazine &magazine) = 0;
    virtual ~Visitor() = default;
};

// 元素接口
class Element {
public:
    virtual void Accept(const std::shared_ptr<Visitor> &visitor) = 0;
    virtual ~Element() = default;
};

// 具体元素：书籍
class Book : public Element {
public:
    void Accept(const std::shared_ptr<Visitor> &visitor) override
    {
        visitor->Visit(*this);
    }

    void Print() const
    {
        std::cout << "Printing Book\n";
    }

    double GetPrice() const
    {
        return 15.0;
    }
};

// 具体元素：杂志
class Magazine : public Element {
public:
    void Accept(const std::shared_ptr<Visitor> &visitor) override
    {
        visitor->Visit(*this);
    }

    void Print() const
    {
        std::cout << "Printing Magazine\n";
    }

    double GetPrice() const
    {
        return 5.0;
    }
};

// 具体访问者：打印访问者
class PrintVisitor : public Visitor {
public:
    void Visit(Book &book) override
    {
        std::cout << "Visiting Book for Printing\n";
        book.Print();
    }

    void Visit(Magazine &magazine) override
    {
        std::cout << "Visiting Magazine for Printing\n";
        magazine.Print();
    }
};

// 具体访问者：价格计算访问者
class PriceVisitor : public Visitor {
public:
    void Visit(Book &book) override
    {
        std::cout << "Calculating price of Book: $" << book.GetPrice() << "\n";
    }

    void Visit(Magazine &magazine) override
    {
        std::cout << "Calculating price of Magazine: $" << magazine.GetPrice() << "\n";
    }
};

// 对象结构：包含元素的集合
class ObjectStructure {

public:
    void AddElement(std::shared_ptr<Element> &element)
    {
        elements_.push_back(element);
    }

    void Accept(const std::shared_ptr<Visitor> &visitor)
    {
        for (auto element : elements_) {
            element->Accept(visitor);
        }
    }

private:
    std::vector<std::shared_ptr<Element>> elements_;
};

void VisitorTest()
{
    // 创建元素
    std::shared_ptr<Element> book = std::make_shared<Book>();
    std::shared_ptr<Element> magazine = std::make_shared<Magazine>();

    // 创建对象结构
    std::shared_ptr<ObjectStructure> object_structure = std::make_shared<ObjectStructure>();
    object_structure->AddElement(book);
    object_structure->AddElement(magazine);

    // 创建访问者
    std::shared_ptr<PrintVisitor> print_visitor = std::make_shared<PrintVisitor>();
    std::shared_ptr<PriceVisitor> price_visitor = std::make_shared<PriceVisitor>();

    // 使用访问者
    std::cout << "Using PrintVisitor:\n";
    object_structure->Accept(print_visitor);

    std::cout << "\nUsing PriceVisitor:\n";
    object_structure->Accept(price_visitor);
}
