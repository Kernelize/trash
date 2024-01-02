#include <any.hpp>
#include <stdexcept>

namespace shits {

Any::Any(const Any& other) {
  type = other.type;
  data = type->copy(other.data);
  flag = 0;
}

Any::Any(Any&& other) {
  type = other.type;
  data = type->move(other.data);
  flag = 0;
}

Any::~Any() {
  if (!(flag & 0B00000001))  // 检查 flag
  {
    if (data && type) {
      type->destroy(data);
    }
  }
}

void Any::foreach (const std::function<void(std::string_view, Any)>& fn) {
  for (auto& [name, field] : type->fields) {
    fn(name, Any(field.first, static_cast<char*>(data) + field.second));
  }
}

Any Any::invoke(std::string_view name, std::span<Any> args) {
  auto it = type->methods.find(name);
  if (it == type->methods.end()) {
    throw std::runtime_error{"method not found"};
  }
  return it->second(data, args);
}

}  // namespace shits
