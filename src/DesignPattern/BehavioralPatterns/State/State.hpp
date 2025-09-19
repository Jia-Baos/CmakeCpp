#pragma once
#include <iostream>
#include <memory>

// 前置声明
class Elevator;
class StopState;
class MovingState;
class OpenDoorState;

// 状态接口：电梯状态
class ElevatorState {
public:
    virtual ~ElevatorState() = default;

    virtual void PressButton(Elevator *elevator) = 0; // 按钮按下
    virtual void OpenDoor(Elevator *elevator) = 0;    // 开门
    virtual void CloseDoor(Elevator *elevator) = 0;   // 关门
    virtual void StartMove(Elevator *elevator) = 0;   // 开始移动
};

// 上下文：电梯类
class Elevator {
public:
    Elevator(const std::shared_ptr<ElevatorState> &state)
        : state_(state) {}

    void SetState(const std::shared_ptr<ElevatorState> &state)
    {
        state_ = state;
    }

    void PressButton()
    {
        state_->PressButton(this);
    }

    void OpenDoor()
    {
        state_->OpenDoor(this);
    }

    void CloseDoor()
    {
        state_->CloseDoor(this);
    }

    void StartMove()
    {
        state_->StartMove(this);
    }

private:
    std::shared_ptr<ElevatorState> state_;
};

// 具体状态：停止状态
class StopState : public ElevatorState {
public:
    void PressButton(Elevator *elevator) override
    {
        std::cout << "Elevator is stopped, moving to next floor..." << std::endl;
        elevator->SetState(std::static_pointer_cast<ElevatorState>(std::make_shared<MovingState>()));
    }

    void OpenDoor(Elevator *elevator) override
    {
        std::cout << "Elevator door is opening..." << std::endl;
        elevator->SetState(std::static_pointer_cast<ElevatorState>(std::make_shared<OpenDoorState>()));
    }

    void CloseDoor(Elevator *elevator) override
    {
        std::cout << "Elevator door is already closed." << std::endl;
    }

    void StartMove(Elevator *elevator) override
    {
        std::cout << "Elevator is already stopped, press button to move." << std::endl;
    }
};

// 具体状态：移动状态
class MovingState : public ElevatorState {
public:
    void PressButton(Elevator *elevator) override
    {
        std::cout << "Elevator is moving, cannot press button." << std::endl;
    }

    void OpenDoor(Elevator *elevator) override
    {
        std::cout << "Elevator is moving, cannot open door." << std::endl;
    }

    void CloseDoor(Elevator *elevator) override
    {
        std::cout << "Elevator door is closing..." << std::endl;
    }

    void StartMove(Elevator *elevator) override
    {
        std::cout << "Elevator is already moving." << std::endl;
    }
};

// 具体状态：开门状态
class OpenDoorState : public ElevatorState {
public:
    void PressButton(Elevator *elevator) override
    {
        std::cout << "Elevator is opening door, cannot move now." << std::endl;
    }

    void OpenDoor(Elevator *elevator) override
    {
        std::cout << "Elevator door is already open." << std::endl;
    }

    void CloseDoor(Elevator *elevator) override
    {
        std::cout << "Elevator door is closing..." << std::endl;
        elevator->SetState(std::make_shared<StopState>());
    }

    void StartMove(Elevator *elevator) override
    {
        std::cout << "Elevator door is open, cannot move now." << std::endl;
    }
};

void StateTest()
{
    // 初始状态为停止状态
    auto stop_state = std::make_shared<StopState>();
    auto elevator = std::make_shared<Elevator>(stop_state);

    // 测试按键事件
    elevator->PressButton(); // 电梯开始移动
    elevator->OpenDoor();    // 电梯开门
    elevator->CloseDoor();   // 电梯关门
    elevator->StartMove();   // 电梯开始移动
}
