#include "../exercise.h"

struct FibonacciCache {
    unsigned long long cache[16] = {0, 1,1}; // 初始化缓存数组为0（可选，但推荐）
    int cached = 2; // 修改为-1，表示还没有缓存任何值
};

static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    if (i == 0) return 0;
    if (i == 1) return 1;
    if (i <= cache.cached) {
        return cache.cache[i]; // 正确访问缓存数组
    }
    // 如果需要，可以先检查cache[0]和cache[1]是否被正确初始化（在这个例子中不需要）
    // 因为在i==0或i==1的情况下函数会直接返回，不会执行到这里
    for (int j = cache.cached + 1; j <= i; ++j) {
        cache.cache[j] = cache.cache[j - 1] + cache.cache[j - 2];
    }
    cache.cached = i; // 更新缓存的最大索引
    return cache.cache[i];
}

int main(int argc, char **argv) {
    FibonacciCache fib; // 这里fib的成员已经被上面的初始化列表初始化了
    // 断言检查fibonacci(10)是否等于55
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
