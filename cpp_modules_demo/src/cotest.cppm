export module cotest;
import std;

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
