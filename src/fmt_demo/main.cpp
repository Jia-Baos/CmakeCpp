#define FMT_HEADER_ONLY

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/color.h>

int main() {
  fmt::print("Hello, world!\n");

  std::string s = fmt::format("The answer is {}", 42);
  fmt::print("{}\n", s);
  
  auto now = std::chrono::system_clock::now();
  fmt::print("The date and time is {}\n", now);
  fmt::print("Time: {:%H:%M}\n", now);

  fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "This is red and bold\n");
  return 0;
}