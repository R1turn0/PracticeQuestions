#include "Fibonacci.h"

class FibonacciImpl : public Fibonacci {
    int FibonacciList(int num) override {
        if (num == 0 || num == 1) {
            return num;
        }
        return FibonacciList(num - 1) + FibonacciList(num - 2);
    }
};

std::unique_ptr<Fibonacci> Fibonacci::create() {
    return std::make_unique<FibonacciImpl>();
}

int ExternFibonacci(int num) {
    if (num == 0 || num == 1) {
        return num;
    }
    return ExternFibonacci(num - 1) + ExternFibonacci(num - 2);
}
