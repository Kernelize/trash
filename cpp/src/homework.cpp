#include <algorithm>
#include <concepts>
#include <format>
#include <functional>
#include <iostream>
#include <numbers>
#include <ranges>
#include <vector>

namespace ranges = std::ranges;

// 1. 实现管道运算符

template <typename U, typename F>
  requires std::regular_invocable<F, U&>
std::vector<U>& operator|(std::vector<U>& v1, F f) {
  ranges::for_each(v1, f);
  return v1;
}

auto htest1() -> void {
  std::vector v{1, 2, 3};
  std::function f{[](const int& i) { std::cout << i << '\n'; }};
  auto f2 = [](int& i) { i *= i; };
  v | f2 | f;
}

// 2. 实现自定义字面量

constexpr auto operator""_f(const char* fmt, std::size_t) {
  return [=]<typename... T>(T&&... args) {
    return std::vformat(fmt, std::make_format_args(std::forward<T>(args)...));
  };
}

auto htest2() -> void {
  std::cout << "乐 :{} *\n"_f(5);
  std::cout << "乐 :{0} {0} *\n"_f(5);
  std::cout << "乐 :{:b} *\n"_f(0b01010101);
  std::cout << "{:*<10}"_f("小黄");
  std::cout << '\n';
  int n{};
  std::cin >> n;
  std::cout << "π：{:.{}f}\n"_f(std::numbers::pi_v<double>, n);
}
