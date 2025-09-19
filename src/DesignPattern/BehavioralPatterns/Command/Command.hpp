#pragma once
#include <iostream>
#include <memory>

namespace Command
{
// 命令接口
class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() = 0;
};

// 接收者类
class Light {
public:
    void TurnOn()
    {
        std::cout << "The light is ON" << std::endl;
    }

    void TurnOff()
    {
        std::cout << "The light is OFF" << std::endl;
    }
};

// 具体命令类：打开灯
class TurnOnLightCommand : public Command {
public:
    TurnOnLightCommand(std::shared_ptr<Light> light)
        : light_(light) {}

    void Execute() override
    {
        light_->TurnOn();
    }

private:
    std::shared_ptr<Light> light_;
};

// 具体命令类：关闭灯
class TurnOffLightCommand : public Command {
public:
    TurnOffLightCommand(std::shared_ptr<Light> light)
        : light_(light) {}

    void Execute() override
    {
        light_->TurnOff();
    }

private:
    std::shared_ptr<Light> light_;
};

// 调用者类
class RemoteControl {
public:
    void SetCommand(std::shared_ptr<Command> command)
    {
        command_ = command;
    }

    void PressButton()
    {
        command_->Execute();
    }

private:
    std::shared_ptr<Command> command_;
};

} // namespace Command

void CommandTest()
{
    // 创建接收者
    auto light = std::make_shared<Command::Light>();

    // 创建具体命令
    auto turn_on_command = std::make_shared<Command::TurnOnLightCommand>(light);
    auto turn_off_command = std::make_shared<Command::TurnOffLightCommand>(light);

    // 创建调用者
    Command::RemoteControl remote;

    // 设置并执行打开命令
    remote.SetCommand(turn_on_command);
    remote.PressButton(); // 输出: The light is ON

    // 设置并执行关闭命令
    remote.SetCommand(turn_off_command);
    remote.PressButton(); // 输出: The light is OFF
}
