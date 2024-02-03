#include <array>
#include <concepts>
// #include <fixed_string.hpp>
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

// using fixstr::fixed_string;
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

// template <fixed_string name, std::size_t offset, typename Type>
// struct Field {};
//
// using FieldInfos = std::tuple<Field<"x", offsetof(Point, x), int>,
//                               Field<"y", offsetof(Point, y), int>>;

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

template <typename... Args>
auto new_print(Args... args) -> void {
  std::println("{}", args...);
}

template <typename T, std::size_t N>
class myarray {
  T arr[N];
};

template <typename T, typename... Args>
myarray(T, Args...)
    -> myarray<std::enable_if_t<(std::is_same_v<T, Args> && ...), T>,
               sizeof...(Args) + 1>;

class Att {
  int a;
  auto foo(this auto& self) -> int { return self.a + 1; }
};

template <typename T>
struct is_void {
  static constexpr bool value = false;
};

template <>
struct is_void<void> {
  static constexpr bool value = true;
};

template <typename T>
constexpr bool is_void_v = is_void<T>::value;

template <typename T>
auto expilicit_instance(T t) -> void {
  std::println("{}", t);
}

template void expilicit_instance<int>(int);
template void expilicit_instance<double>(double);

void shiihf() { auto v = vector{2, 3, 4}; }

template <typename...>
struct type_seq {};

template <typename... Ts>
auto f(Ts...[0] arg, type_seq<Ts...>) {
  return arg;
}

constexpr auto size(auto... Is) {
  std::vector<int> v = {Is...};
  return v.size();
}

void for_each(auto&& object, auto&& func) {
  using T = std::remove_cvref_t<decltype(object)>;
}

template <typename T>
struct S11 {
  template <typename U>
  void foo() {}
};

template <typename T>
void bar111() {
  S11<T> s;
  s.template foo<int>();
}

// name binding
void gg(double){};

template <typename T>
struct S12 {
  void f() const { gg(1); }
};

void gg(int){};

void test734() {
  gg(1);  // invoke g(int)
  S12<int> s;
  s.f();  // invoke g(double)
}

// SFINAE
template <typename A>
struct B1 {
  using type = A::type;
  // use typename before C++20
};

template <typename T, typename U = T::type, typename V = typename B1<T>::type>
void foo5(int) {
  std::println("SFINAE T::type B<T>::type");
}

template <typename T>
void foo5(double) {
  std::println("SFINAE T");
}

void test5() {
  struct C {
    using type = int;
  };
  foo5<B1<C>>(1);  // calls foo(int)
  foo5<void>(1);   // calls foo(double)
}

// 我需要写一个函数模板 add，想要要求传入的对象必须是支持
// operator+的，应该怎么写？ use SFINAE:
template <typename T>
auto add(const T& t1, const T& t2) -> decltype(t1 + t2) {
  std::println("SFINAE +");
  return t1 + t2;
}
// 1. 这样有啥好处吗？使用了 SFINAE
// 看起来还变复杂了。我就算不用这写法，如果对象没有 operator+
// 不是一样会编译错误吗？
// 2. 虽然前面说了 SFINAE
// 可以影响重载决议，我知道这个很有用，但是我这个函数根本没有别的重载，这样写还是有必要的吗？
// 这两个问题其实是一个问题，本质上就是还是不够懂 SFINAE 或者说模板：

// 如果就是简单写一个 add 函数模板不使用
// SFINAE，那么编译器在编译的时候，会尝试模板实例化，生成函数定义，发现你这类型根本没有
// operator+，于是实例化模板错误。

// 如果按照我们上面的写法使用
// SFINAE，根据“代换失败不是错误”的规则，从重载集中丢弃这个特化
// add，然而又没有其他的 add 重载，所以这里的错误是“未找到匹配的重载函数”。

// 这里的重点是什么？是模板实例化，能不要实例化就不要实例化，我们当前的示例只是因为
// add
// 函数模板非常的简单，即使实例化错误，编译器依然可以很轻松的报错告诉你，是因为没有
// operator+。但是很多模板是非常复杂的，编译器实例化模板经常会产生一些完全不可读的报错；如果我们使用
// SFINAE，编译器就是直接告诉我：“未找到匹配的重载函数”，我们自然知道就是传入的参数没有满足要求。而且实例化模板也是有开销的，很多时候甚至很大。

// 总而言之： 即使不为了处理重载，使用 SFINAE
// 约束函数模板的传入类型，也是有很大好处的：报错、编译速度。

// 我要写一个函数模板 add，我要求传入的对象需要支持 + 以及它需要有别名 type
// ，成员 value、f
template <typename T,
          typename SFINAE = std::void_t<decltype(T{} + T{}), typename T::type,
                                        decltype(&T::value), decltype(&T::f)>>
auto add2(const T& t1, const T& t2) {
  return t1 + t2;
}
// decltype(T{} + T{}) 这个表达式中，同时要求了 T
// 类型支持默认构造（虽然这不是我们的本意），然而我们的 X2
// 类型没有默认构造，自然而然 T{}
// 不是合法表达式，代换失败。其实我们之前也有类似的写法，我们在本节进行纠正，使用
// std::declval：
template <typename T, typename SFINAE = std::void_t<
                          decltype(std::declval<T>() + std::declval<T>())>>
auto add3(const T& t1, const T& t2) {
  std::puts("SFINAE +");
  return t1 + t2;
}

// concepts
template <typename T>
concept Addable = requires(T a) { a + a; };

template <Addable T>
auto add4(const T& t1, const T& t2) {
  std::puts("concepts +");
  return t1 + t2;
}

// a b都必须是整数类型
auto max3(const std::integral auto& a, const std::integral auto& b)
    -> decltype(auto) {
  return a > b ? a : b;
}

// template <class _Tp>
// concept integral = is_integral_v<_Tp>;
// 这也告诉各位我们一件事情：定义概念（concept）
// 时声明的约束表达式，只需要是编译期可得到 bool 类型的表达式即可。

// 我相信你这里一定有疑问：“那么我们之前写的 requires 表达式呢？它会返回 bool
// 值吗？” 对，简单的说，把模板参数带入到 requires
// 表达式中，是否符合语法，符合就返回 true，不符合就返回 false。在 requires
// 表达式 一节中会详细讲解。
// 这是否直观了很多？并且概念不单单是可以用作简写函数模板中的
// auto，还有几乎一切语境，比如： int f() { return 0; } std::integral auto
// result = f();
//
// requires 表达式: requires() {}
// 简单的说，把模板参数带入到 requires 表达式中，是否符合语法，符合就返回
// true，不符合就返回 false
template <typename It>
auto my_distance(It first, It last) -> size_t {
  using category = typename std::iterator_traits<It>::iterator_category;
  if constexpr (std::is_same_v<category, std::random_access_iterator_tag>) {
    return last - first;
  } else {
    size_t count = 0;
    while (first != last) {
      ++first;
      ++count;
    }
    return count;
  }
};
