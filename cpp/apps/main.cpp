import std;

auto main() -> int {
  std::println("Hello, world!");
  auto v = std::views::iota(0, 10) |
           std::views::transform([](auto x) { return x * x; }) |
           std::ranges::to<std::vector<int>>();
  for (auto x : v) {
    std::println("{}", x);
  }
}
