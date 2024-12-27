#include "../exercise.h"

class Fibonacci {
    size_t cache[16]; // 缓存数组
    int cached;       // 已缓存的斐波那契数数量

public:
    // 构造器，初始化前两个斐波那契数和缓存计数器
    Fibonacci() : cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 计算斐波那契数列的第i个值（从0开始计数）
    size_t get(int i) {
        // 如果i小于已缓存的数量，直接返回缓存中的值
        if (i < cached) {
            return cache[i];
        }

        // 计算并填充缓存中缺失的值
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }

        // 更新已缓存的数量
        cached = i + 1;

        // 返回所需的斐波那契数
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会直接调用。
    // 这个写法不再是未定义行为了。
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}