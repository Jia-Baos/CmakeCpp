#define FMT_HEADER_ONLY

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/color.h>

#include <iostream>
#include <thread>
#include <atomic>
#include <future>
#include <mutex>
#include <shared_mutex>

class Base {
 public:
  static std::uint64_t getID() {
    static std::shared_mutex m_mutex_;
    static std::atomic<std::uint64_t> m_task_id_{0};
    {
      std::unique_lock<std::shared_mutex> lock(m_mutex_);
      // fmt::print("Base::getID() {}\n", m_task_id_);
      std::cout << "Base::getID(), " << m_task_id_ << std::endl;
      ++m_task_id_;
    }

    return m_task_id_;
  }
};

// 静态成员函数需要在类外定义，否则会出现未定义的符号错误，因为静态成员变量的初始化是在类外进行的
// 对于头文件被多次引用的情况，建议将静态成员变量的初始化放在 .cpp 文件中，并在头文件中声明为 extern，
// 这样可以避免多次定义，提高编译速度
// std::atomic<std::uint64_t> Base::m_task_id_ = 0;
// std::shared_mutex Base::m_mutex_;

class Derived1 : public Base {
 public:
  void newTask() {
    auto id = Base::getID();
    // fmt::print("Derived1::foo() {}\n", id);
    std::cout << "Derived1::foo(), " << id << std::endl;
  }
};

class Derived2 : public Base {
 public:
  void newTask() {
    auto id = Base::getID();
    // fmt::print("Derived2::foo() {}\n", id);
    std::cout << "Derived2::foo(), " << id << std::endl;
  }
};

void task1(std::promise<bool> prom) {
  std::cout << "task1 start." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  prom.set_value(true);
}

void task2(std::future<bool> fut) {
  std::cout << "task2 start, " << fut.valid() << std::endl;
  std::cout << "fut val: " << fut.get() << std::endl;
  std::cout << "task2 end, " << fut.valid() << std::endl;
}

int main() {
  fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "This is red and bold\n");

  std::thread([] {
    std::cout << "thread 1 start\n";
    Derived1 d1;
    d1.newTask();
  }).join();

  std::thread([] {
    std::cout << "thread 2 start\n";
    Derived2 d2;
    d2.newTask();
  }).join();

  std::thread([] {
    std::cout << "thread 3 start\n";
    Derived1 d1;
    d1.newTask();
    Derived2 d2;
    d2.newTask();
  }).join();

  std::promise<bool> prom;
  std::future<bool> fut = prom.get_future();
  std::thread t1(task1, std::move(prom));
  std::thread t2(task2, std::move(fut));

  t1.detach();
  t2.join();

  return 0;
}
