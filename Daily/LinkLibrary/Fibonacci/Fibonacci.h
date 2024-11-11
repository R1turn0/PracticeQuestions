#ifndef LINKLIBRARY_FIBONACCI_H
#define LINKLIBRARY_FIBONACCI_H

#include <memory>

// 跨平台导出宏
#if defined(_WIN32)
#ifdef SIMPLEMATH_EXPORTS
#define SIMPLEMATH_API __declspec(dllexport)
#else
#define SIMPLEMATH_API __declspec(dllimport)
#endif
#else
#define SIMPLEMATH_API __attribute__((visibility("default")))
#endif

class /*SIMPLEMATH_API*/ Fibonacci {
public:
    virtual ~Fibonacci() = default;

    static std::unique_ptr<Fibonacci> create();

    virtual int FibonacciList(int num) = 0;

    // 禁用拷贝
    Fibonacci(const Fibonacci &) = delete;

    Fibonacci &operator=(const Fibonacci &) = delete;

protected:
    Fibonacci() = default;
};

extern "C" {
int ExternFibonacci(int num);
};

#endif //LINKLIBRARY_FIBONACCI_H
