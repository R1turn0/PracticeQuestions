#include <iostream>
#include "Fibonacci.h"

int main() {
    auto fib = Fibonacci::create();
    std::cout << fib->FibonacciList(10) << std::endl;
    return 0;
}
