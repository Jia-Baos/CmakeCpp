#pragma once
#include <iostream>
#include <memory>
#include <mutex>

/* 单例模式 */

/**
 * @brief 饿汉模式
 *
 */
class SingletonEager {
public:
    static SingletonEager &GetInstance()
    {
        return m_instance;
    }

    void Display()
    {
        std::cout << "m_call_Count: " << m_call_count << std::endl;
    }

private:
    SingletonEager()
    {
        std::cout << "SingletonEager constructor called" << std::endl;
    }
    ~SingletonEager()
    {
        std::cout << "SingletonEager destructor called" << std::endl;
    }

    SingletonEager(const SingletonEager &) = delete;
    SingletonEager &operator=(const SingletonEager &) = delete;

private:
    static size_t m_call_count;
    static SingletonEager m_instance;
};

size_t SingletonEager::m_call_count = 0;
SingletonEager SingletonEager::m_instance; // 程序启动时就被创建

/**
 * @brief 此版本不会调用析构函数，需要手动释放
 *
 */
class SingletonLazy {
public:
    static SingletonLazy *GetInstance()
    {
        if (m_instance == nullptr) {
            { // 双重检查版本
                std::lock_guard<std::mutex> lock(m_mtx);
                if (m_instance == nullptr) {
                    m_instance = new SingletonLazy(); // 第一次使用时才被 new 出来
                    ++m_call_count;
                }
            }
        }

        return m_instance;
    }

    void Display()
    {
        std::cout << "m_call_Count: " << m_call_count << std::endl;
    }

private:
    SingletonLazy()
    {
        std::cout << "SingletonLazy constructor called" << std::endl;
    }
    ~SingletonLazy()
    {
        std::cout << "SingletonLazy destructor called" << std::endl;
    }

    SingletonLazy(const SingletonLazy &) = delete;
    SingletonLazy &operator=(const SingletonLazy &) = delete;

private:
    static std::mutex m_mtx;
    static size_t m_call_count;
    static SingletonLazy *m_instance;
};

std::mutex SingletonLazy::m_mtx;
size_t SingletonLazy::m_call_count = 0;
SingletonLazy *SingletonLazy::m_instance = nullptr;

/**
 * @brief 此版本构造函数和析构函数需要为 public
 *
 */
class SingletonLazyUnique {
public:
    static std::unique_ptr<SingletonLazyUnique> &GetInstance()
    {
        if (m_instance == nullptr) {
            { // 双重检查版本
                std::lock_guard<std::mutex> lock(m_mtx);
                if (m_instance == nullptr) {
                    m_instance = std::make_unique<
                        SingletonLazyUnique>(); // 第一次使用时才被 new 出来
                    ++m_call_count;
                }
            }
        }

        return m_instance;
    }

    void Display()
    {
        std::cout << "m_call_Count: " << m_call_count << std::endl;
    }

    // unique_ptr 下需要构造函数和析构函数显示定义
    SingletonLazyUnique()
    {
        std::cout << "SingletonLazyUnique constructor called" << std::endl;
    }
    ~SingletonLazyUnique()
    {
        std::cout << "SingletonLazyUnique destructor called" << std::endl;
    }

private:
    SingletonLazyUnique(const SingletonLazyUnique &) = delete;
    SingletonLazyUnique &operator=(const SingletonLazyUnique &) = delete;

private:
    static std::mutex m_mtx;
    static size_t m_call_count;
    static std::unique_ptr<SingletonLazyUnique> m_instance;
};

std::mutex SingletonLazyUnique::m_mtx;
size_t SingletonLazyUnique::m_call_count = 0;
std::unique_ptr<SingletonLazyUnique> SingletonLazyUnique::m_instance = nullptr;

/**
 * @brief C++11 后推荐写法
 *
 */
class SingletonBest {
public:
    static SingletonBest &GetInstance()
    {
        static SingletonBest instance; // 静态局部变量
        ++m_call_count;
        return instance;
    }

    void Display()
    {
        std::cout << "m_call_Count: " << m_call_count << std::endl;
    }

private:
    SingletonBest()
    {
        std::cout << "SingletonBest constructor called" << std::endl;
    }
    ~SingletonBest()
    {
        std::cout << "SingletonBest destructor called" << std::endl;
    }

    SingletonBest(const SingletonBest &) = delete;            // 禁止拷贝构造函数
    SingletonBest &operator=(const SingletonBest &) = delete; // 禁止赋值

private:
    static size_t m_call_count;
};

size_t SingletonBest::m_call_count = 0;

/**
 * @brief 单例模式测试
 *
 */
void SingletonTest()
{
    SingletonEager &singleton_eager1 = SingletonEager::GetInstance();
    singleton_eager1.Display();

    SingletonEager &singleton_eager2 = SingletonEager::GetInstance();
    singleton_eager2.Display();

    SingletonLazy *singleton_lazy1 = SingletonLazy::GetInstance();
    singleton_lazy1->Display();

    SingletonLazy *singleton_lazy2 = SingletonLazy::GetInstance();
    singleton_lazy2->Display();

    auto &singleton_lazy_unique1 = SingletonLazyUnique::GetInstance();
    singleton_lazy_unique1->Display();

    auto &singleton_lazy_unique2 = SingletonLazyUnique::GetInstance();
    singleton_lazy_unique2->Display();

    SingletonBest &singleton_best1 = SingletonBest::GetInstance();
    singleton_best1.Display();

    SingletonBest &singleton_best2 = SingletonBest::GetInstance();
    singleton_best2.Display();
}
