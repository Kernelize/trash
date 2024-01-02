#include <array>
#include <concepts>
#include <fixed_string.hpp>
#include <iostream>
#include <numeric>
#include <optional>
#include <print>
#include <string_view>
#include <test.hpp>
#include <tuple>
#include <type_traits>
#include <vector>

#define let auto
#define fn auto

using fixstr::fixed_string;
using std::vector;

using namespace std::string_literals;

struct FieldInfo {
  std::string_view name;
  std::size_t offset;
  std::size_t size;
};

struct Point {
  int x;
  int y;
};

constexpr std::array<FieldInfo, 2> fieldInfos = {{
    {"x", offsetof(Point, x), sizeof(int)},
    {"y", offsetof(Point, y), sizeof(int)},
}};

template <fixed_string name, std::size_t offset, typename Type>
struct Field {};

using FieldInfos = std::tuple<Field<"x", offsetof(Point, x), int>,
                              Field<"y", offsetof(Point, y), int>>;

template <std::size_t N, typename T, typename F>
void helper(T t, F f) {
  f(std::get<N>(t));
}

template <typename Tuple, typename Func>
constexpr void access(std::size_t index, Tuple&& tuple, Func&& f) {
  constexpr auto length = std::tuple_size<std::decay_t<decltype(tuple)>>::value;
  using FuncType = void (*)(decltype(tuple), decltype(f));
  constexpr auto fn_table = []<std::size_t... I>(std::index_sequence<I...>) {
    std::array<FuncType, length> table = {
        helper<I, decltype(tuple), decltype(f)>...};
    return table;
  }(std::make_index_sequence<length>{});
  return fn_table[index](std::forward<Tuple>(tuple), std::forward<Func>(f));
}

// struct Foo {
//   auto func(this Self& self) { return 1; }
// };

template <typename T, template <typename, typename> typename C>
struct foo1 {};

template <typename A, template <typename> typename B,
          template <template <typename> typename> typename C>
struct foo2 {};

// Use std::decay_t to ensure that the type is not a reference type.
template <typename T1, typename T2,
          typename RT = std::decay_t<decltype(true ? T1{} : T2{})>>
RT max2(const T1& lhs, const T2& rhs) {
  return lhs > rhs ? lhs : rhs;
}
// equivalent to
auto max1(const auto& lhs, const auto& rhs) -> decltype(true ? lhs : rhs) {
  return lhs > rhs ? lhs : rhs;
}

template <class... Args>
auto sum1(Args... args) {
  return (... + args);
}

template <typename... Args>
auto print1(Args... args) -> void {
  auto _[]{(std::print("{}", args), 0)...};
}

template <size_t N>
auto print2() -> void {
  std::print("{}", N);
}

template <typename... Args>
auto print3(Args... args) -> void {
  auto _[]{(std::print("{}", args), 0)...};  // &args is the 'pattern'
}

template <typename T, typename IndexType>
concept Indexable = requires(T t, IndexType i) {
  { t[i] } -> std::convertible_to<typename T::value_type>;
};

template <typename T, typename... Types>
concept IsAllTypeTheSame = (std::same_as<T, Types> && ...);

template <typename T, typename Index, typename... Indexes>
  requires Indexable<T, Index> && IsAllTypeTheSame<Index, Indexes...>
auto print_array(T& arr, Index index, Indexes... indexes) -> void {
  std::println("{} ", arr[index]);
  if constexpr (sizeof...(indexes) != 0) {
    int _[]{(std::print("{}", indexes), 0)...};
  }
}

template <typename... Args>
auto println_array(Args... args) {
  print_array(args...);
  std::println("");
}

template <typename... Args, typename RT = std::common_type_t<Args...>>
auto sum2(Args... args) -> RT {
  RT _[]{args...};
  return std::accumulate(std::begin(_), std::end(_), RT{});
}

template <class... Args>
auto sum3(Args... args) {
  return (... + args);
}

template <typename T>
struct Foo3 {
  T t;
  Foo3(T t) : t{t} {}
};

// User defined deduction guide
Foo3(int) -> Foo3<size_t>;

template <typename T, std::size_t N>
struct array1 {
  T arr[N];
};

template <typename T, typename... Args>
array1(T, Args...) -> array1<T, 1 + sizeof...(Args)>;

template <typename... Args>
struct X1 {
  std::tuple<Args...> inner;
  X1(Args... args) : inner{args...} {};
};

