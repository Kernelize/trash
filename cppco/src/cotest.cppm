export module cotest;
import std;

// clang-format off
#if !defined(__cpp_size_t_suffix) || __cpp_size_t_suffix < 202011L
inline constexpr auto operator""uz(unsigned long long const value)
{
	return std::size_t{ value };
}

inline constexpr auto operator""z(unsigned long long const value)
{
	return std::ptrdiff_t(value);
}
#endif
// clang-format on

export namespace co {
class BasicCoroutine {
public:
  struct Promise {
    BasicCoroutine get_return_object() { return BasicCoroutine{}; }

    void unhandled_exception() noexcept {}

    void return_void() noexcept {}

    std::suspend_never initial_suspend() noexcept { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
  };
  using promise_type = Promise;
};

BasicCoroutine coro() {
  co_await std::suspend_never();
  co_return;
}

class thread_pool {
public:
  thread_pool(std::size_t num);
  ~thread_pool();
  void exit();
  class context;
  static context capture_context() noexcept;
  void run_in(std::coroutine_handle<> callback, context ctx);
  void run_after(std::coroutine_handle<> callback,
                 std::chrono::milliseconds duration);
  void run_once(std::coroutine_handle<> callback, std::size_t priority);
};

template <typename T>
class task;

template<>
class task<void>;

} // namespace co

// BasicCoroutine coro() { co_return; }
/* The above following function expands to:
 * ReturnType someCoroutine(Parameters parameter) {
 *   auto *frame = new coroutineFrame(std::forward<Parameters>(parameters));
 *   auto returnObject = frame->promise.get_return_object();
 *   co_await frame->promise.initial_suspend();
 *   try {
 *     <body-statements>
 *   } catch (...) {
 *     frame->promise.unhandled_exception();
 *   }
 *   co_await frame->promise.final_suspend();
 *   delete frame;
 *   return returnObject;
 * }
 */

/*
 * When an awaitable is co_awaited, the operator co_await is executed and the
 * awaiter is obtained from it. Then awaiter.await_ready() is called. If it
 * returns true, the coroutine does not suspend and await_resume is called
 * immediately, producing the return value of the expression. This is how
 * std::suspend_never works - It simply returns true from await_ready()! If
 * await_ready is false, the coroutine is suspended, meaning all state necessary
 * to resume it later is stored in the coroutine state and await_suspend is
 * called, being passed a std::coroutine_handle to the coroutine being
 * suspended. Among other things and most importantly this handle can be used to
 * resume the coroutine later. When a suspended coroutine is resumed,
 * await_resume is called, returning the result to be produced by the co_await
 * expression.
 */
