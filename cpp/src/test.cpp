#include <algorithm>
#include <any.hpp>
#include <array>
#include <cstdio>
#include <matchit.hpp>
#include <print>
#include <stdexcept>
#include <test.hpp>
#include <ranges>

namespace ranges = std::ranges;
namespace views = std::views;

template <typename T, std::size_t N>
constexpr std::array<T, N> compile_time_sort(std::array<T, N> arr) {
  std::sort(arr.begin(), arr.end());
  return arr;
}
void test() {
  constexpr std::array<int, 5> arr = {5, 3, 4, 1, 2};
  constexpr auto sorted_arr = compile_time_sort(arr);
}

void test2() {
  using namespace matchit;
  auto a = 1.0, b = 2.0;
  auto cmp = a <=> b;
  // C++ 20起，>=, <=, >, < 和!= 运算符分别是由 <=> 和 == 生成的
  auto c = match(a <=> b)(
      pattern | std::partial_ordering::less =
          [] {
            std::println("less");
            return 0;
          },
      pattern | std::partial_ordering::greater =
          [] {
            std::println("greater");
            return 1;
          },
      pattern | std::partial_ordering::equivalent =
          [] {
            std::println("equivalent");
            return 2;
          },
      pattern | std::partial_ordering::unordered =
          [] {
            std::println("unordered");
            return 3;
          },
      pattern | _ =
          [] {
            throw std::runtime_error("unreachable!");
            return -1;
          });

  struct Person {
    std::string name;
    uint8_t age;
  };

  // auto const value = Person{"John", 23};
  // auto const name_age = dsVia(&Person::name, name_pat, &Person::age,
  // age_pat); Id<std::string> person_name; match(value)(
  //     pattern | name_age(person_name, 18 <= _ && _ <= 150) = []{}
  // );
  constexpr auto x = std::make_optional(3);
  Id<int32_t> y;
  match(x)(
      // No need to worry about y's type, by ref or by value is automatically
      // managed by `match(it)` library.
      pattern | some(y) = [] {});
}

// 位域
struct EightBools {
  bool b1 : 1;
  bool b2 : 1;
  bool b3 : 1;
  bool b4 : 1;
  bool b5 : 1;
  bool b6 : 1;
  bool b7 : 1;
  bool b8 : 1;
};  // sizeof(EightBools) == 1

void test3() {
  auto a = EightBools{};
  auto size_a = sizeof a;

  auto& [b1, b2, b3, b4, b5, b6, b7, b8] = a;
}

struct hfoo2 {
  int a;
  int b;
};

void test4() {
  // {} 是什么？ 花括号初始化器列表, 没有类型,不是表达式, decltype({1, 2})非良构

  // 无法推导
  // auto b {1, 2};

  // 例外:复制列表初始化均推导为 std::initializer_list<T>
  auto a = {1, 2};

  // 指派初始化
  hfoo2 b = {.a = 1, .b = 2};

  auto [_, _] = b;

  auto vec = std::vector{hfoo2{1, 2}};
  auto vec2 = vec | views::all | views::reverse | ranges::to<std::vector>();
}

void test5() {
  auto a = std::vector{1, 2, 3};
  for (int i = 0; i < a.size(); i++) {
    std::printf("%d\n", a[i]);
  }
}
