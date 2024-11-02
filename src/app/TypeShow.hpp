#pragma
#include <cstdlib>
#include <iostream>
#include <string>

#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#endif

template <typename T> std::string cpp_type_name() {
  std::string name = typeid(T).name();
  std::string res{};
#if defined(__GNUC__) || defined(__clang__)
  int status;
  const char *p = abi::__cxa_demangle(name.c_str(), nullptr, 0, &status);

  if (status != 0) {
    switch (status) {
    case -1:
      res = "memory allocation error";
      break;
    case -2:
      res = "invalid name given";
      break;
    case -3:
      res = "internal error: __cxa_demangle: invalid argument";
      break;
    default:
      res = "unknown error occured";
      break;
    }
  }

  res = p;
  // std::free(p);
#else
  std::string s = name;
#endif
  if (std::is_const_v<std::remove_reference_t<T>>)
    res += " const";
  if (std::is_volatile_v<std::remove_reference_t<T>>)
    res += " volatile";
  if (std::is_lvalue_reference_v<T>)
    res += " &";
  if (std::is_rvalue_reference_v<T>)
    res += " &&";
  return res;
}

#define SHOW(T) std::cout << cpp_type_name<T>() << std::endl;