#include <cstdint>
#include <functional>
#include <span>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <typeinfo>

namespace shits {

struct Type;

template <typename T>
Type* type_of();

class Any {
 private:
  Type* type;    // type info
  void* data;    // data
  uint8_t flag;  // 1 if not owned, don't call destructor

 public:
  Any() : type(nullptr), data(nullptr), flag(0) {}
  Any(Type* type, void* data) : type(type), data(data), flag(1) {}
  Any(const Any& other);
  Any(Any&& other);

  // 用于装箱
  template <typename T>
  Any(T&& value);

  ~Any();

  // 用于拆箱
  template <typename T>
  T& cast();

  Type* GetType() const { return type; }

  // to invoke methods
  Any invoke(std::string_view name, std::span<Any> args);

  // to traverse fields
  void foreach (const std::function<void(std::string_view, Any)>& fn);
};

template <typename T>
T& Any::cast() {
  if (type != type_of<T>()) {
    throw std::runtime_error{"type mismatch"};
  }
  return *static_cast<T*>(data);
}

struct Type {
  using Destroy = void (*)(void*);
  using Construct = void* (*)(void*);
  using Method = Any (*)(void*, std::span<Any>);
  using Field = std::pair<Type*, std::size_t>;

  std::string_view name;
  Destroy destroy;
  Construct copy;
  Construct move;
  std::unordered_map<std::string_view, Field> fields;
  std::unordered_map<std::string_view, Method> methods;
};

template <typename T>
struct member_fn_traits;

template <typename R, typename C, typename... Args>
struct member_fn_traits<R (C::*)(Args...)> {
  using return_type = R;
  using class_type = C;
  using args_type = std::tuple<Args...>;
};

template <auto ptr>
auto* type_ensure() {
  using traits = member_fn_traits<decltype(ptr)>;
  using class_type = typename traits::class_type;
  using result_type = typename traits::return_type;
  using args_type = typename traits::args_type;

  return +[](void* object, std::span<Any> args) -> Any {
    auto self = static_cast<class_type*>(object);
    return [=]<std::size_t... Is>(std::index_sequence<Is...>) {
      if constexpr (std::is_void_v<result_type>) {
        (self->*ptr)(args[Is].cast<std::tuple_element_t<Is, args_type>>()...);
        return Any{};
      } else {
        auto result = (self->*ptr)(
            args[Is].cast<std::tuple_element_t<Is, args_type>>()...);
        return Any{result};
      }
    }(std::make_index_sequence<std::tuple_size_v<args_type>>{});
  };
}

template <typename T>
Type* type_of()
{
    static Type type;
    type.name = typeid(T).name();
    type.destroy = [](void* obj) { delete static_cast<T*>(obj); };
    type.copy = [](void* obj) { return (void*)(new T(*static_cast<T*>(obj))); };
    type.move = [](void* obj) { return (void*)(new T(std::move(*static_cast<T*>(obj)))); };
    return &type;
}

template <typename T>
Any::Any(T&& value) // 用于对值类型装箱
{
    type = type_of<std::decay_t<T>>();
    data = new std::decay_t<T>(std::forward<T>(value));
    flag = 0;
}

// template <auto ptr>
// auto type_ensure2() -> auto* {
//   using traits = member_fn_traits<decltype(ptr)>;
//   using class_type = typename traits::class_type;
//   using result_type = typename traits::return_type;
//   using args_type = typename traits::args_type;
//
//   return +[](void* object, std::span<Any> args) -> Any {
//     auto self = static_cast<class_type*>(object);
//     return [=]<std::size_t... Is>(std::index_sequence<Is...>) {
//       if constexpr (std::is_void_v<result_type>) {
//         // return type is void
//         (self->*ptr)(args[Is].cast<std::tuple_element_t<Is, args_type>>()...);
//         return Any{};
//       } else {
//         return Any{(self->*ptr)(
//             args[Is].cast<std::tuple_element_t<Is, args_type>>()...)};
//       }
//     }(std::make_index_sequence<std::tuple_size_v<args_type>>{});
//   };
// }

}  // namespace shits
