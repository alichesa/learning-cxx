#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>

class DynFibonacci {
    size_t *cache;  // 缓存数组
    int capacity;   // 容量
    int cached;     // 已缓存的元素个数

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]), capacity(capacity), cached(2) {
        // 初始化前两个斐波那契数
        cache[0] = 0;
        cache[1] = 1;
    }

    // 复制构造器
    DynFibonacci(DynFibonacci const &other) 
        : cache(new size_t[other.capacity]), capacity(other.capacity), cached(other.cached) {
        // 复制缓存内容
        std::copy(other.cache, other.cache + other.capacity, cache);
    }

    // 析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;  // 释放缓存数组
    }

    // 获取第 i 个斐波那契数
    size_t get(int i) {
        // 优化：如果缓存中没有该值，计算并缓存
        if (i >= cached) {
            for (int j = cached; j <= i; ++j) {
                if (j < capacity) {
                    cache[j] = cache[j - 1] + cache[j - 2];
                }
            }
            cached = std::max(cached, i + 1);  // 更新已缓存的元素数量
        }
        return cache[i];
    }

    // 常量版本的 get 方法，返回缓存中的值
    size_t get(int i) const {
        if (i < cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
        return 0;  // 防止编译器警告，实际不会执行到这里
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
