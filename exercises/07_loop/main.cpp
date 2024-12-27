#include "../exercise.h"


static unsigned long long fibonacci(int i) {
    // 缓存设置正确的初始值
    static unsigned long long cache[96] = {0, 1}; // 初始化前两个斐波那契数
    static int maxComputed = 1; // 记录已计算的最大索引

    // 如果所需的值已经计算过，直接返回
    if (i <= maxComputed) {
        return cache[i];
    }

    // 计算未缓存的值
    for (int j = maxComputed + 1; j <= i; ++j) {
        cache[j] = cache[j - 1] + cache[j - 2];
    }

    // 更新已计算的最大索引
    maxComputed = i;

    return cache[i];
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(fibonacci(0) == 0, "fibonacci(0) should be 0");
    ASSERT(fibonacci(1) == 1, "fibonacci(1) should be 1");
    ASSERT(fibonacci(2) == 1, "fibonacci(2) should be 1");
    ASSERT(fibonacci(3) == 2, "fibonacci(3) should be 2");
    ASSERT(fibonacci(10) == 55, "fibonacci(10) should be 55");

    auto fib90 = fibonacci(90);
    std::cout << "fibonacci(90) = " << fib90 << std::endl;
    ASSERT(fib90 == 2880067194370816120, "fibonacci(90) should be 2880067194370816120");
    return 0;
}