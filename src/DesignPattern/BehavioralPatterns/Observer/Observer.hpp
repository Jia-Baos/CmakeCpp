#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

// 观察者接口
class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(float temperature, float humidity, float pressure) = 0;
};

// 主题接口
class Subject {
public:
    virtual ~Subject() = default;
    virtual void RegisterObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void RemoveObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void NotifyObservers() = 0;
};

// 具体主题：气象站
class WeatherData : public Subject {
public:
    void SetMeasurements(float temperature, float humidity, float pressure)
    {
        temperature_ = temperature;
        humidity_ = humidity;
        pressure_ = pressure;
        NotifyObservers();
    }

    void RegisterObserver(std::shared_ptr<Observer> observer) override
    {
        observers_.push_back(observer);
    }

    void RemoveObserver(std::shared_ptr<Observer> observer) override
    {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

    void NotifyObservers() override
    {
        for (auto &observer : observers_) {
            observer->Update(temperature_, humidity_, pressure_);
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers_;
    float temperature_{ 0.0f };
    float humidity_{ 0.0f };
    float pressure_{ 0.0f };
};

// 具体观察者：手机显示
class PhoneDisplay : public Observer {
public:
    void Update(float temperature, float humidity, float pressure) override
    {
        temperature_ = temperature;
        humidity_ = humidity;
        pressure_ = pressure;
        Display();
    }

    void Display()
    {
        std::cout << "Phone display updated: "
                  << "Temperature: " << temperature_
                  << "C, Humidity: " << humidity_
                  << "%, Pressure: " << pressure_
                  << "hPa" << std::endl;
    }

private:
    float temperature_{ 0.0f };
    float humidity_{ 0.0f };
    float pressure_{ 0.0f };
};

// 具体观察者：电视显示
class TVDisplay : public Observer {
public:
    void Update(float temperature, float humidity, float pressure) override
    {
        temperature_ = temperature;
        humidity_ = humidity;
        pressure_ = pressure;
        Display();
    }

    void Display()
    {
        std::cout << "TV display updated: "
                  << "Temperature: " << temperature_
                  << "C, Humidity: " << humidity_
                  << "%, Pressure: " << pressure_
                  << "hPa" << std::endl;
    }

private:
    float temperature_{ 0.0f };
    float humidity_{ 0.0f };
    float pressure_{ 0.0f };
};

void ObserverTest()
{
    // 创建气象站（主题）
    auto weather_data = std::make_shared<WeatherData>();

    // 创建观察者
    auto phone_display = std::make_shared<PhoneDisplay>();
    auto tv_display = std::make_shared<TVDisplay>();

    // 注册观察者
    weather_data->RegisterObserver(phone_display);
    weather_data->RegisterObserver(tv_display);

    // 模拟气象数据变化
    weather_data->SetMeasurements(25.0f, 65.0f, 1013.0f);
    weather_data->SetMeasurements(26.5f, 70.0f, 1012.5f);
    weather_data->SetMeasurements(22.0f, 60.0f, 1010.0f);
}
