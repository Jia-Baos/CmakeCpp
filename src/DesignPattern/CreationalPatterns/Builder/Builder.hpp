#pragma once
#include <iostream>

// 产品类：Computer
class Computer {
public:
    void SetCpu(const std::string &cpu)
    {
        m_cpu_ = cpu;
    }
    void SetRam(const std::string &ram)
    {
        m_ram_ = ram;
    }
    void SetHardDrive(const std::string &hardDrive)
    {
        m_hard_drive_ = hardDrive;
    }
    void SetMonitor(const std::string &monitor)
    {
        m_monitor_ = monitor;
    }

    void DisplayConfiguration()
    {
        std::cout << "Computer Configuration:" << std::endl;
        std::cout << "CPU: " << m_cpu_ << std::endl;
        std::cout << "RAM: " << m_ram_ << std::endl;
        std::cout << "Hard Drive: " << m_hard_drive_ << std::endl;
        std::cout << "Monitor: " << m_monitor_ << std::endl;
    }

private:
    std::string m_cpu_;
    std::string m_ram_;
    std::string m_hard_drive_;
    std::string m_monitor_;
};

// 抽象建造者类
class ComputerBuilder {
public:
    virtual ~ComputerBuilder() = default;
    virtual void BuildCpu() = 0;
    virtual void BuildRam() = 0;
    virtual void BuildHardDrive() = 0;
    virtual void BuildMonitor() = 0;
    virtual Computer *GetComputer() = 0;
};

// 具体建造者类
class GamingComputerBuilder : public ComputerBuilder {
public:
    GamingComputerBuilder()
    {
        m_computer_ = new Computer();
    }

    void BuildCpu() override
    {
        m_computer_->SetCpu("Intel i9");
    }
    void BuildRam() override
    {
        m_computer_->SetRam("32GB DDR4");
    }
    void BuildHardDrive() override
    {
        m_computer_->SetHardDrive("1TB SSD");
    }
    void BuildMonitor() override
    {
        m_computer_->SetMonitor("27-inch 144Hz");
    }

    Computer *GetComputer() override
    {
        return m_computer_;
    }

private:
    Computer *m_computer_;
};

/**
 * @brief 指导者决定具体创建哪些部件
 *
 */
class Director {
public:
    Director(ComputerBuilder *builder)
        : m_builder_(builder) {}

    Computer *Construct()
    {
        m_builder_->BuildCpu();
        m_builder_->BuildRam();
        m_builder_->BuildHardDrive();
        m_builder_->BuildMonitor();
        return m_builder_->GetComputer();
    }

private:
    ComputerBuilder *m_builder_;
};

/**
 * @brief 建造者模式测试
 *
 */
void BuilderTest()
{
    ComputerBuilder *computer_builder = new GamingComputerBuilder(); // 具体的创建者
    Director *director = new Director(computer_builder);             // 指导者

    Computer *computer = director->Construct(); // 通过指导者获取创建出来的物体
    computer->DisplayConfiguration();

    delete computer;
    delete director;
    delete computer_builder;
}
