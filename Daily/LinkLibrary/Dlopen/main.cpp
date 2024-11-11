#include <iostream>
#include "Dlopen.h"

int main() {
    try {
        auto fib = Dlopen("./libFibonacci.so");
        fib.register_common_functions();
        std::cout << fib.Fibonacci(10) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
