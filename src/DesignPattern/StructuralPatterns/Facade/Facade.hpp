#pragma once
#include <iostream>

// 子系统 1：灯光
class Light {
public:
    void On()
    {
        std::cout << "Light is On" << std::endl;
    }
    void Off()
    {
        std::cout << "Light is Off" << std::endl;
    }
};

// 子系统 2：音响
class SoundSystem {
public:
    void TurnOn()
    {
        std::cout << "Sound System is On" << std::endl;
    }
    void TurnOff()
    {
        std::cout << "Sound System is Off" << std::endl;
    }
};

// 子系统 3：空调
class AirConditioner {
public:
    void TurnOn()
    {
        std::cout << "Air Conditioner is On" << std::endl;
    }
    void TurnOff()
    {
        std::cout << "Air Conditioner is Off" << std::endl;
    }
};

// 外观类
class HomeTheaterFacade {
private:
    Light *light_;
    SoundSystem *sound_system_;
    AirConditioner *air_conditioner_;

public:
    HomeTheaterFacade(Light *l, SoundSystem *s, AirConditioner *a)
        : light_(l), sound_system_(s), air_conditioner_(a) {}

    void StartMovieNight()
    {
        std::cout << "Starting Movie Night..." << std::endl;
        light_->Off();
        sound_system_->TurnOn();
        air_conditioner_->TurnOn();
    }

    void EndMovieNight()
    {
        std::cout << "Ending Movie Night..." << std::endl;
        light_->On();
        sound_system_->TurnOff();
        air_conditioner_->TurnOff();
    }
};

void FacadeTest()
{
    // 创建子系统对象
    Light *light = new Light();
    SoundSystem *sound_system = new SoundSystem();
    AirConditioner *air_conditioner = new AirConditioner();

    // 创建外观对象
    HomeTheaterFacade home_theater(light, sound_system, air_conditioner);

    // 客户端通过外观接口操作系统
    home_theater.StartMovieNight();
    std::cout << "Enjoying the movie!" << std::endl;
    home_theater.EndMovieNight();
}
