#include <iostream>
#include <ranges>
#include <format>

namespace views = std::views;
namespace ranges = std::ranges;

int main() {
    for (auto i: views::iota(0, 1)) {
        std::cout << std::format("{}", i) << '\n';
    }
    return 0;
}
