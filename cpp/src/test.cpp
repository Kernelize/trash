#include <stdexcept>
#include <test.hpp>
#include <any.hpp>
#include <matchit.hpp>
#include <print>

void test() {
  auto a = 1, b = 2;
  auto c = a <=> b;
  auto da = 1.0, db = 2.0;
  auto dc = da <=> db;
}

void test2() {
  using namespace matchit;
  auto a = 1.0, b = 2.0;
  auto cmp = a <=> b;
  auto c = match(a <=> b)(
    pattern | std::partial_ordering::less = [] { std::println("less"); return 0; },
    pattern | std::partial_ordering::greater = [] { std::println("greater"); return 1; },
    pattern | std::partial_ordering::equivalent = [] { std::println("equivalent"); return 2; },
    pattern | std::partial_ordering::unordered = [] { std::println("unordered"); return 3; },
    pattern | _ = [] { throw std::runtime_error("unreachable!"); return -1; }
  );

  struct Person {
     std::string name;
     uint8_t age;
  };

  // auto const value = Person{"John", 23};
  // auto const name_age = dsVia(&Person::name, name_pat, &Person::age, age_pat);
  // Id<std::string> person_name;
  // match(value)(
  //     pattern | name_age(person_name, 18 <= _ && _ <= 150) = []{}
  // );
  constexpr auto x = std::make_optional(3);
  Id<int32_t> y;
  match(x)(
      // No need to worry about y's type, by ref or by value is automatically managed by `match(it)` library.
      pattern | some(y) = []{}
  );
}
