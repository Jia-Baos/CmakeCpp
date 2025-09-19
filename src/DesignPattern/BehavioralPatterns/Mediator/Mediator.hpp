#pragma once
#include <vector>
#include <iostream>
#include <memory>

// 前置声明
class Colleague;

// 中介者接口
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void Send(const std::string &message, Colleague *colleague) = 0;
};

// 同事类基类
class Colleague {
public:
    Colleague(std::shared_ptr<Mediator> mediator)
        : mediator(mediator) {}
    virtual ~Colleague() = default;

    void SendMessage(const std::string &message)
    {
        mediator->Send(message, this);
    }

    virtual void ReceiveMessage(const std::string &message) = 0;

protected:
    std::shared_ptr<Mediator> mediator;
};

// 具体同事类：用户
class User : public Colleague {
public:
    User(std::shared_ptr<Mediator> mediator, const std::string &name)
        : Colleague(mediator), name_(name) {}

    void ReceiveMessage(const std::string &message) override
    {
        std::cout << name_ << " received: " << message << std::endl;
    }

    const std::string &GetName() const
    {
        return name_;
    }

    bool operator!=(const User &other) const
    {
        return name_ != other.name_;
    }

private:
    std::string name_;
};

// 具体中介者：聊天室
class ChatRoom : public Mediator {
public:
    void AddUser(std::shared_ptr<User> user)
    {
        users_.push_back(user);
    }

    void Send(const std::string &message, Colleague *colleague) override
    {
        // 找到发送消息的用户
        User *sender = static_cast<User *>(colleague);
        for (auto &user : users_) {
            // 发送消息给聊天室中的其他用户
            if (*user != *sender) {
                user->ReceiveMessage(sender->GetName() + ": " + message);
            }
        }
    }

private:
    std::vector<std::shared_ptr<User>> users_;
};

void MediatorTest()
{
    // 创建聊天室中介者
    auto chat_room = std::make_shared<ChatRoom>();

    // 创建用户
    auto user1 = std::make_shared<User>(chat_room, "Alice");
    auto user2 = std::make_shared<User>(chat_room, "Bob");
    auto user3 = std::make_shared<User>(chat_room, "Charlie");

    // 将用户添加到聊天室
    chat_room->AddUser(user1);
    chat_room->AddUser(user2);
    chat_room->AddUser(user3);

    // 用户发送消息
    user1->SendMessage("Hi, everyone!");
    user2->SendMessage("Hello Alice!");
    user3->SendMessage("Hey there!");
}
