//
// Created by 71466 on 20/9/2025.
//

#ifndef LINKLIBRARY_DLOPEN_H
#define LINKLIBRARY_DLOPEN_H

#include <functional>
#include <string>
#include <dlfcn.h>

class Dlopen {
public:
    explicit Dlopen(const std::string &library_path);

    ~Dlopen();

    // 禁止拷贝
    Dlopen(const Dlopen &) = delete;

    Dlopen &operator=(const Dlopen &) = delete;

    // 加载函数模板
    template<typename Signature>
    std::function<Signature> load(const std::string &name);

    // 注册并存储常用函数
    void register_common_functions();

    int Fibonacci(int num);

private:
    void *handle_;
    std::function<int(int)> Fibonacci_;
};


#endif //LINKLIBRARY_DLOPEN_H
