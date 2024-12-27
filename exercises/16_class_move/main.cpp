#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // 构造函数：动态分配内存，初始化斐波那契数列
    DynFibonacci(int capacity)
        : cache(new size_t[capacity]), cached(2), capacity(capacity) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 移动构造函数：转移资源的所有权
    DynFibonacci(DynFibonacci &&other) noexcept 
        : cache(other.cache), cached(other.cached), capacity(other.capacity) {
        other.cache = nullptr;  // 让源对象指针为空，避免析构时释放内存
        other.cached = 0;       // 重置源对象的缓存状态
        other.capacity = 0;     // 重置容量
    }

    // 移动赋值运算符：处理资源的转移并避免自赋值
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) {  // 避免自赋值
            delete[] cache;  // 释放当前对象的资源

            cache = other.cache;        // 转移资源
            cached = other.cached;
            capacity = other.capacity;

            other.cache = nullptr;  // 让源对象指针为空
            other.cached = 0;       // 重置源对象的缓存状态
            other.capacity = 0;     // 重置容量
        }
        return *this;
    }

    // 析构函数：释放动态分配的内存
    ~DynFibonacci() {
        delete[] cache;
    }

    // 运算符重载：根据索引获取斐波那契数
    size_t operator[](int i) {
        if (i >= cached) {
            for (int j = cached; j <= i; ++j) {
                cache[j] = cache[j - 1] + cache[j - 2];
            }
            cached = std::max(cached, i + 1);
        }
        return cache[i];
    }

    // 常量版本的运算符重载
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // 检查对象是否存活
    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    // 移动构造，fib 的资源转移到 fib_
    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    // 移动赋值，fib1 的资源转移到 fib0
    fib0 = std::move(fib1);

    // 移动赋值到自身，应该不发生错误
    fib0 = std::move(fib0);

    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
