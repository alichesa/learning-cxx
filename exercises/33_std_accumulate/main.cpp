#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>
// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // 调用 `std::transform`，将 `val` 中的每个元素乘以 2，并转换为字符串，存入 `ans`
    std::vector<std::string> ans(val.size());
    std::transform(val.begin(), val.end(), ans.begin(), [](int v) {
        return std::to_string(v * 2);
    });

    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");

    // 计算张量占用的字节数
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    int size = std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<int>()) * sizeof(DataType);
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");

    return 0;
}
