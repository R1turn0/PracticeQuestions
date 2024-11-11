//
// Created by 71466 on 20/9/2025.
//

#include <iostream>
#include "Dlopen.h"

Dlopen::Dlopen(const std::string &library_path) {
    handle_ = dlopen(library_path.c_str(), RTLD_LAZY);
    if (!handle_) {
        throw std::runtime_error("Failed to open library: " + std::string(dlerror()));
    }
}

Dlopen::~Dlopen() {
    if (handle_) {
        dlclose(handle_);
    }
}

template<typename Signature>
std::function<Signature> Dlopen::load(const std::string &funcName) {
    dlerror(); // 清除之前的错误
    void *sym = dlsym(handle_, funcName.c_str());
    if (const char *error = dlerror()) {
        throw std::runtime_error("Failed to load symbol '" + funcName + "': " + error);
    }
    return reinterpret_cast<Signature *>(sym);
}

void Dlopen::register_common_functions() {
    Fibonacci_ = load<int(int)>("ExternFibonacci");
}

int Dlopen::Fibonacci(int num) {
    if (!Fibonacci_) throw std::runtime_error("Fibonacci function not loaded");
    return Fibonacci_(num);
}