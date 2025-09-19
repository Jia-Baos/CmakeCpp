#pragma once
#include <iostream>
#include <memory>

// 抽象处理者
class Handler {
public:
    virtual ~Handler() = default;

    // 设置下一个处理者
    void SetNext(std::shared_ptr<Handler> nextHandler)
    {
        next = nextHandler;
    }

    // 处理请求的接口
    virtual void HandleRequest(int request) = 0;

protected:
    std::shared_ptr<Handler> next; // 下一个处理者
};

// 具体的处理者
class ConcreteHandlerA : public Handler {
public:
    void HandleRequest(int request) override
    {
        if (request >= 0 && request < 10) {
            std::cout << "Handler A handle request: " << request << std::endl;
        } else if (next) {
            next->HandleRequest(request); // 传递给下一个处理者
        }
    }
};

class ConcreteHandlerB : public Handler {
public:
    void HandleRequest(int request) override
    {
        if (request >= 10 && request < 20) {
            std::cout << "Handler B handle request: " << request << std::endl;
        } else if (next) {
            next->HandleRequest(request); // 传递给下一个处理者
        }
    }
};

class ConcreteHandlerC : public Handler {
public:
    void HandleRequest(int request) override
    {
        if (request >= 20) {
            std::cout << "Handler C handle request: " << request << std::endl;
        } else if (next) {
            next->HandleRequest(request); // 传递给下一个处理者
        }
    }
};

void ChainofResponsibilityTest()
{
    // 创建处理者
    auto handler_a = std::make_shared<ConcreteHandlerA>();
    auto handler_b = std::make_shared<ConcreteHandlerB>();
    auto handler_c = std::make_shared<ConcreteHandlerC>();

    // 建立责任链
    handler_a->SetNext(handler_b);
    handler_b->SetNext(handler_c);

    // 发起请求
    handler_a->HandleRequest(5);  // 输出: Handler A处理请求: 5
    handler_a->HandleRequest(15); // 输出: Handler B处理请求: 15
    handler_a->HandleRequest(25); // 输出: Handler C处理请求: 25
}
