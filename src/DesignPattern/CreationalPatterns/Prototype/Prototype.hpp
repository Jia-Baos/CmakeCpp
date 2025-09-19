#pragma once
#include <iostream>

// 原型接口
class Shape {
public:
    virtual ~Shape() {}
    virtual Shape *Clone() const = 0; // 克隆方法
    virtual void Draw() const = 0;    // 绘制方法
};

// 具体原型类：Circle
class Circle : public Shape {
public:
    Circle()
        : radius_(0) {}
    Circle(int r)
        : radius_(r) {}

    // 实现克隆方法
    Shape *Clone() const override
    {
        return new Circle(*this); // 深拷贝
    }

    // 绘制方法
    void Draw() const override
    {
        std::cout << "Drawing Circle with radius " << radius_ << std::endl;
    }

    void SetRadius(int r)
    {
        radius_ = r;
    }

private:
    int radius_;
};

// 具体原型类：Rectangle
class Rectangle : public Shape {
public:
    Rectangle()
        : width_(0), height_(0) {}
    Rectangle(int w, int h)
        : width_(w), height_(h) {}

    // 实现克隆方法
    Shape *Clone() const override
    {
        return new Rectangle(*this); // 深拷贝
    }

    // 绘制方法
    void Draw() const override
    {
        std::cout << "Drawing Rectangle with width " << width_ << " and height " << height_ << std::endl;
    }

    void SetDimensions(int w, int h)
    {
        width_ = w;
        height_ = h;
    }

private:
    int width_, height_;
};

/**
 * @brief 原型模式测试
 *
 */
void PrototypeTest()
{
    // 创建一个 Circle 对象
    Circle *circle1 = new Circle(10);
    circle1->Draw(); // 输出：Drawing Circle with radius 10

    // 克隆 Circle 对象
    Shape *circle2 = circle1->Clone();
    circle2->Draw(); // 输出：Drawing Circle with radius 10

    // 创建一个 Rectangle 对象
    Rectangle *rectangle1 = new Rectangle(20, 30);
    rectangle1->Draw(); // 输出：Drawing Rectangle with width 20 and height 30

    // 克隆 Rectangle 对象
    Shape *rectangle2 = rectangle1->Clone();
    rectangle2->Draw(); // 输出：Drawing Rectangle with width 20 and height 30

    // 清理内存
    delete circle1;
    delete circle2;
    delete rectangle1;
    delete rectangle2;
}
