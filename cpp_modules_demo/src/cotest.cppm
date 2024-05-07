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
