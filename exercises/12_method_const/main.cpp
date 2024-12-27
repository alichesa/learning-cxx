#include "../exercise.h"

struct Fibonacci {
    int numbers[11];

    // 修改方法签名，使其为 const 成员函数并支持 constexpr
    constexpr int get(int i) const {
        return numbers[i];
    }
};

int main(int argc, char **argv) {
    // 定义一个 constexpr 的 Fibonacci 对象
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};

    // 测试并输出结果
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;

    return 0;
}
