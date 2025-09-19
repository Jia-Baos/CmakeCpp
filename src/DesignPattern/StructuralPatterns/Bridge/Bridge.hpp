#pragma once
#include <iostream>

namespace Bridge
{
// 实现接口
class RenderAPI {
public:
    virtual ~RenderAPI() {}
    virtual void RenderCircle(float x, float y, float radius) = 0;
    virtual void RenderRectangle(float x, float y, float width, float height) = 0;
};

// 具体实现类 1：OpenGL 渲染
class OpenGLRenderAPI : public RenderAPI {
public:
    void RenderCircle(float x, float y, float radius) override
    {
        std::cout << "Rendering Circle using OpenGL at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }

    void RenderRectangle(float x, float y, float width, float height) override
    {
        std::cout << "Rendering Rectangle using OpenGL at (" << x << ", " << y << ") with width " << width
                  << " and height " << height << std::endl;
    }
};

// 具体实现类 2：DirectX 渲染
class DirectXRenderAPI : public RenderAPI {
public:
    void RenderCircle(float x, float y, float radius) override
    {
        std::cout << "Rendering Circle using DirectX at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }

    void RenderRectangle(float x, float y, float width, float height) override
    {
        std::cout << "Rendering Rectangle using DirectX at (" << x << ", " << y << ") with width " << width
                  << " and height " << height << std::endl;
    }
};

// 抽象类：Shape
class Shape {
public:
    virtual ~Shape() {}
    virtual void Draw() = 0; // 抽象绘制方法

protected:
    RenderAPI *render_api; // 通过桥接，抽象类持有实现接口的指针

    // 构造函数接受一个实现接口
    Shape(RenderAPI *renderAPI)
        : render_api(renderAPI) {}
};

// 精化抽象类：Circle
class Circle : public Shape {
public:
    Circle(float x, float y, float radius, RenderAPI *renderAPI)
        : Shape(renderAPI), x_(x), y_(y), radius_(radius) {}

    void Draw() override
    {
        render_api->RenderCircle(x_, y_, radius_); // 使用桥接的实现接口绘制
    }

private:
    float x_, y_, radius_;
};

// 精化抽象类：Rectangle
class Rectangle : public Shape {
public:
    Rectangle(float x, float y, float width, float height, RenderAPI *renderAPI)
        : Shape(renderAPI), x_(x), y_(y), width_(width), height_(height) {}

    void Draw() override
    {
        render_api->RenderRectangle(x_, y_, width_, height_); // 使用桥接的实现接口绘制
    }

private:
    float x_, y_, width_, height_;
};
} // namespace Bridge

void BridgeTest()
{
    // 创建具体实现类（OpenGL 渲染和 DirectX 渲染）
    Bridge::RenderAPI *open_gl_render_api = new Bridge::OpenGLRenderAPI();
    Bridge::RenderAPI *direct_x_render_api = new Bridge::DirectXRenderAPI();

    // 创建具体抽象类（Circle 和 Rectangle）
    Bridge::Shape *circle = new Bridge::Circle(10.0f, 20.0f, 5.0f, open_gl_render_api);
    Bridge::Shape *rectangle = new Bridge::Rectangle(30.0f, 40.0f, 10.0f, 20.0f, direct_x_render_api);

    // 绘制图形，具体的实现通过桥接接口选择
    circle->Draw();    // 输出：Rendering Circle using OpenGL at (10, 20) with radius 5
    rectangle->Draw(); // 输出：Rendering Rectangle using DirectX at (30, 40) with width 10 and height 20

    // 清理内存
    delete circle;
    delete rectangle;
    delete open_gl_render_api;
    delete direct_x_render_api;
}
