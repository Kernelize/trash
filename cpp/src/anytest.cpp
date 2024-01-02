#include <any.hpp>
#include <iostream>
#include <print>

using shits::Any;
using shits::type_of;

struct Person {
  std::string_view name;
  std::size_t age;

  void say(std::string_view msg) { std::println("{} say: {}", name, msg); }
};

template <>
shits::Type* shits::type_of<Person>() {
  static Type type;
  type.name = "Person";
  type.destroy = [](void* obj) { delete static_cast<Person*>(obj); };
  type.copy = [](void* obj) {
    return (void*)(new Person(*static_cast<Person*>(obj)));
  };
  type.move = [](void* obj) {
    return (void*)(new Person(std::move(*static_cast<Person*>(obj))));
  };
  type.fields.insert(
      {"name", {type_of<std::string_view>(), offsetof(Person, name)}});
  type.fields.insert({"age", {type_of<std::size_t>(), offsetof(Person, age)}});
  type.methods.insert({"say", type_ensure<&Person::say>()});
  return &type;
};

auto anytest1() -> void {
  Any person = Person{"Tom", 18};
  std::vector<Any> args = {std::string_view{"Hello"}};
  person.invoke("say", args);
  // => Tom say: Hello
  auto f = [](std::string_view name, Any value) {
    if (value.GetType() == type_of<std::string_view>()) {
      std::cout << name << " = " << value.cast<std::string_view>() << std::endl;
    } else if (value.GetType() == type_of<std::size_t>()) {
      std::cout << name << " = " << value.cast<std::size_t>() << std::endl;
    }
  };

  person.foreach (f);
  // =>
  // name = Tom
  // age = 18
}
