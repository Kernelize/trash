import std;

template <typename T, typename... Ts>
auto appendToTuple(const std::tuple<Ts...>& t, const T& item) {
  return std::tuple_cat(t, std::make_tuple(item));
}

auto main() -> int {
  auto v = std::make_tuple(1, 2, 3);
  auto v2 = appendToTuple(v, 'c');
  std::println("{}", v2);
}
