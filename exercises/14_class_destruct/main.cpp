#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;  // 缓存数组指针
    int capacity;   // 缓存容量
    int cached;     // 已计算的斐波那契数的个数

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity): capacity(capacity), cached(2) {  // 从计算第2项开始
        if (capacity <= 0) {
            cache = nullptr;
            return;
        }
        
        cache = new size_t[capacity];  // 动态分配缓存空间
        
        // 初始缓存值
        cache[0] = 0;  // Fibonacci(0) = 0
        if (capacity > 1) cache[1] = 1;  // Fibonacci(1) = 1
    }

    // 析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;  // 释放动态分配的缓存空间
    }

    // 优化的斐波那契计算方法
    size_t get(int i) {
        // 如果缓存中没有计算过该数值，则进行计算并缓存
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];  // 斐波那契递推公式
        }

        // 调试输出，查看缓存状态
        std::cout << "cache[" << i << "] = " << cache[i] << std::endl;

        return cache[i];  // 返回缓存中的斐波那契值
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
