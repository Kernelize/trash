#include <iostream>
#include <thread>

void f(int) { std::cout << "Hello World\n"; }

int main_bitch() {
  std::thread t{f, 1};
  t.join();
  auto a = sizeof(std::thread);
}
