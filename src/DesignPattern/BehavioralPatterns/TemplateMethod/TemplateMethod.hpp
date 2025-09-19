#pragma once
#include <vector>
#include <iostream>
#include <memory>

namespace TemplateMethod
{
/* 模板模式 */
/**
 * @brief 只有一个策略，并且需要基类的成员函数实现多态
 *
 */
struct Character {
public:
    void Update()
    {
        Move();
        Draw();
    }

protected:
    virtual void Draw() = 0;
    virtual void Move() = 0;
};

struct Player : Character {
    void Draw() override
    {
        std::cout << "Player draw" << std::endl;
    }
    void Move() override
    {
        std::cout << "Player move" << std::endl;
    }
};

struct Enemy : Character {
    void Draw() override
    {
        std::cout << "Enemy draw" << std::endl;
    }
    void Move() override
    {
        std::cout << "Enemy move" << std::endl;
    }
};

struct Game {
    std::vector<std::shared_ptr<Character>> chars{};
    void Update()
    {
        for (auto &&iter : chars) {
            iter->Update();
        }
    }
};

struct Weapon {

public:
    void Update(const std::shared_ptr<Enemy> &enemy)
    {
        Attack(enemy);
    }

protected:
    double damage;
    double charge;
    double range;

    virtual void Attack(const std::shared_ptr<Enemy> &enemy) {}
};

struct Converter {
protected:
    virtual void DoProcess(const char *s, size_t len) = 0;

public:
    void Process(std::string_view str)
    {
        return DoProcess(str.data(), str.size());
    }
};

// 抽象类：饮料
class CaffeineBeverage {
public:
    // 模板方法
    void PrepareRecipe()
    {
        BoilWater();
        Brew();
        PourInCup();
        AddCondiments();
    }

    virtual ~CaffeineBeverage() = default;

private:
    void BoilWater()
    {
        std::cout << "Boiling water\n";
    }

    void PourInCup()
    {
        std::cout << "Pouring into cup\n";
    }

    // 具体子类实现
    virtual void Brew() = 0;          // 不同的饮料如何“冲泡”是不同的
    virtual void AddCondiments() = 0; // 不同的饮料加的调味品不同
};

// 具体类：做咖啡
class Coffee : public CaffeineBeverage {
protected:
    void Brew() override
    {
        std::cout << "Dripping coffee through filter\n";
    }

    void AddCondiments() override
    {
        std::cout << "Adding sugar and milk\n";
    }
};

// 具体类：做茶
class Tea : public CaffeineBeverage {
protected:
    void Brew() override
    {
        std::cout << "Steeping the tea\n";
    }

    void AddCondiments() override
    {
        std::cout << "Adding lemon\n";
    }
};
} // namespace TemplateMethod

void TemplateMethodTest()
{
    // 使用模板方法
    TemplateMethod::Coffee coffee;
    std::cout << "Making coffee:\n";
    coffee.PrepareRecipe(); // 会调用模板方法

    std::cout << "\nMaking tea:\n";
    TemplateMethod::Tea tea;
    tea.PrepareRecipe(); // 会调用模板方法
}
