#include <cstddef>
#include <iterator>
template <typename T, typename U>
struct is_same {
  static constexpr bool value = false;
};

template <typename T>
struct is_same<T, T> {
  static constexpr bool value = true;
};

template <typename T>
struct remove_const {
  using type = T;
};

template <typename T>
struct remove_const<const T> {
  using type = T;
};

template <typename T>
struct remove_reference {
  using type = T;
};

template <typename T>
struct remove_reference<T&> {
  using type = T;
};

template <typename It>
size_t distance(It first, It last) {
  using category = typename std::iterator_traits<It>::iterator_category;

  if constexpr (is_same<category, std::random_access_iterator_tag>::value) {
    return last - first;
  } else {
    size_t count = 0;
    while (first != last) {
      ++first;
      ++count;
    }
    return count;
  }
}
