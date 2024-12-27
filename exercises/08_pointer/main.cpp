#include "../exercise.h"
 
bool is_fibonacci(int *ptr, int len, int stride) {
    if (len < 3) {
        return false;
    }
 
    // 查找非零的起始元素
    int start_idx = 0;
    while (start_idx < len && (ptr[start_idx * stride] == 0 || ptr[(start_idx + 1) * stride] == 0)) {
        start_idx++;
    }
 
    // 如果没有找到两个非零的起始元素，则不是斐波那契数列
    if (start_idx >= len - 1) {
        return false;
    }
 
    int a = ptr[start_idx * stride];
    int b = ptr[(start_idx + 1) * stride];
 
    // 从第三个有效元素开始检查斐波那契数列的性质
    for (int i = start_idx + 2; i < len; i++) {
        int c = ptr[i * stride];
        if (c != a + b) {
            return false;
        }
        a = b;
        b = c;
    }
 
    return true;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    int arr0[]{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55},
        arr1[]{0, 1, 2, 3, 4, 5, 6},
        arr2[]{99, 98, 4, 1, 7, 2, 11, 3, 18, 5, 29, 8, 47, 13, 76, 21, 123, 34, 199, 55, 322, 0, 0};
    // clang-format off
    ASSERT( is_fibonacci(arr0    , sizeof(arr0) / sizeof(*arr0)    , 1),         "arr0 is Fibonacci"    );
    ASSERT( is_fibonacci(arr0 + 2, sizeof(arr0) / sizeof(*arr0) - 4, 1), "part of arr0 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr1    , sizeof(arr1) / sizeof(*arr1)    , 1),         "arr1 is not Fibonacci");
    ASSERT( is_fibonacci(arr1 + 1,  3                              , 1), "part of arr1 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2    , sizeof(arr2) / sizeof(*arr2)    , 1),         "arr2 is not Fibonacci");
    ASSERT( is_fibonacci(arr2 + 2, 10                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT( is_fibonacci(arr2 + 3,  9                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2 + 3, 10                              , 2), "guard check"                  );
    ASSERT(!is_fibonacci(arr2 + 1, 10                              , 2), "guard check"                  );
    // clang-format on
    return 0;
}